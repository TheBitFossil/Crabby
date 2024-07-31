// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter2D.h"

#include "Enemy.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WallDetectorComponent.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerHUD.h"
#include "Components/ProgressBar.h"

APlayerCharacter2D::APlayerCharacter2D()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	AttackCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Attack Collision Detector"));
	AttackCollisionBox->SetupAttachment(RootComponent);

	WallDetectorComponentForward = CreateDefaultSubobject<UWallDetectorComponent>(TEXT("Wall Detector"));
	WallDetectorComponentForward->SetupAttachment(RootComponent);
}

//---------------------------------

void APlayerCharacter2D::BeginPlay()
{
	Super::BeginPlay();

	if(APlayerController* PC = static_cast<APlayerController*>(GetController()))
	{
		// Setup some bindings - we are currently using Enhanced Input and just using some input actions assigned in editor for simplicity
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Default, 0);
		}
	}

	/* notify when animation is complete*/
	OnAttackOverrideEndDelegate.BindUObject(this, &APlayerCharacter2D::OnAttackOverrideEndSequence);
	AttackCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter2D::OnAttackCollisionBeginOverlap);

	GetCharacterMovement()->GravityScale = CustomGravityScale;
	ToggleAttackCollisionBox(false);

	if(PlayerHudClass)
	{
		PlayerHudWidget = CreateWidget<UPlayerHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0), PlayerHudClass);
		if(PlayerHudWidget)
		{
			PlayerHudWidget->AddToPlayerScreen();

			PlayerHudWidget->SetDiamonds(10);
			PlayerHudWidget->SetHealth(Health);
			PlayerHudWidget->SetLevel(1);
			PlayerHudWidget->SetDashCoolDown(DashCooldownTime);
		}
	}
}

//---------------------------------

void APlayerCharacter2D::SetDirectionFacing(const float ActionValue)
{
	if(!Controller || MovementState == EMoveState::MOVE_Wall)
	{
		return;
	}
	
	FRotator NewRotation = GetControlRotation();

	// IF its 0.f then no change for the current Value
	NewRotation.Yaw = (ActionValue < 0.f) ? 180.f : (ActionValue > 0.f) ? 0.f : NewRotation.Yaw;
	Controller->SetControlRotation(NewRotation);
}

//---------------------------------

void APlayerCharacter2D::Move(const FInputActionValue& InputActionValue)
{
	if(!Controller || bIsStunned)
	{
		return;
	}
	
	const float ActionValue = InputActionValue.Get<float>();
		
	if(bIsAlive && bIsMovementAllowed)
	{
		const FVector Direction = FVector(1.f, 0.f, 0.f); 
		AddMovementInput(Direction, ActionValue);
		SetDirectionFacing(ActionValue);
	}
}

//---------------------------------

void APlayerCharacter2D::MoveCompleted(const FInputActionValue& InputActionValue)
{
	if(!Controller || bIsStunned)
	{
		return;
	}
	
	
	FRotator LastRotation = GetControlRotation();
	Controller->SetControlRotation(FRotator(LastRotation.Pitch, LastRotation.Yaw, LastRotation.Roll));
}

//---------------------------------

void APlayerCharacter2D::StartJump(const FInputActionValue& InputActionValue)
{
	if(!bIsAlive || bIsStunned)
	{
		return;
	}

	switch (MovementState)
	{
	case EMoveState::MOVE_Ground:
		Jump();
		break;
	case EMoveState::MOVE_Air:
		// DoubleJump()
		break;
	case EMoveState::MOVE_Wall:
		WallJump();
		break;
	}
}

//---------------------------------

void APlayerCharacter2D::StopJump(const FInputActionValue& InputActionValue)
{
	StopJumping();
}

//---------------------------------

void APlayerCharacter2D::Attack(const FInputActionValue& InputActionValue)
{
	if(!bIsAlive || bIsStunned)
	{
		return;
	}
	
	if(bCanAttack)
	{
		bCanAttack = false;
		bIsMovementAllowed = false;
		
		GetAnimInstance()->PlayAnimationOverride(
			AttackAnimationSequence,
			FName("DefaultSlot"),
			1,
			0,
			OnAttackOverrideEndDelegate
		);
	}
}

//---------------------------------

void APlayerCharacter2D::Dash(const FInputActionValue& InputActionValue)
{
	if(!bCanDash)
	{
		return;
	}

	const FVector DashDirection = GetActorForwardVector();
	LaunchCharacter(DashDirection * DashForce, true, true);
	bCanDash = false;
	bIsImmortal = true;
	
	GetWorldTimerManager().SetTimer(DashTimerDelegate,
		this,
		&APlayerCharacter2D::OnDashTimerTimeOut,
		1.f,
		false,
		DashCooldownTime
	);
}

//---------------------------------

void APlayerCharacter2D::ToggleGravity(const bool Enabled) const
{
	UCharacterMovementComponent* CMC = GetCharacterMovement();
	if(!CMC)
	{
		return;
	}
	
	if(Enabled)
	{
		CMC->GravityScale = CustomGravityScale;
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Normal"));
	}
	else
	{
		CMC->GravityScale = WallJumpGravityScale;
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Low Gravity"));
	}
}

//---------------------------------

void APlayerCharacter2D::OnDashTimerTimeOut()
{
	bCanDash = true;
	bIsImmortal = false;
	
	PlayerHudWidget->SetDashCoolDown(DashCooldownTime);
}

//---------------------------------

void APlayerCharacter2D::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if(MovementState != EMoveState::MOVE_Ground)
	{
		MovementState = EMoveState::MOVE_Ground;
	}
}

//---------------------------------

void APlayerCharacter2D::WallJump()
{
	if(MovementState != EMoveState::MOVE_Wall || !GetCharacterMovement())
	{
		return;
	}

	const FVector DirNormal = (-GetActorForwardVector() + GetActorUpVector()).GetSafeNormal();
	const FVector JumpDirection = DirNormal * WallJumpForce;

	ToggleGravity(false);

	LaunchCharacter(JumpDirection, true, true);	// Get some distance from the Wall

	//SetDirectionFacing(-1);								// Turn around

	GetWorldTimerManager().SetTimer(
		WallJumpTimerDelegate,
		this,
		&APlayerCharacter2D::OnWallJumpTimerTimeOut,
		WallHangDuration,
		false
	);
}

//---------------------------------

void APlayerCharacter2D::OnAttackOverrideEndSequence(bool Completed)
{
	if(!bIsAlive || !Completed)
	{
		return;
	}

	bCanAttack = true;
	bIsMovementAllowed = true;
}

//---------------------------------

void APlayerCharacter2D::ToggleAttackCollisionBox(bool Enabled)
{
	if(Enabled)
	{
		AttackCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		AttackCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
	else
	{
		AttackCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		AttackCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	}
}

//---------------------------------

void APlayerCharacter2D::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();

	LastJumpLocation = GetActorLocation();
}

//---------------------------------

void APlayerCharacter2D::OnWallJumpTimerTimeOut()
{
	MovementState = EMoveState::MOVE_Air;
	ToggleGravity(true);
}

//---------------------------------

void APlayerCharacter2D::OnStunTimerTimeOut()
{
	bIsStunned = false;
}

//---------------------------------

void APlayerCharacter2D::OnHealthTickTimeout()
{
	if(LastHealth > Health)
	{
		LastHealth -= HealthRemovePerTick;
		float Percent = FMath::Clamp(LastHealth / 100.f, 0.f, 1.f);
		PlayerHudWidget->HealthProgressBarDelayed->SetPercent(Percent);
	}
	else if(LastHealth <= Health)
	{
		LastHealth = Health;
		GetWorldTimerManager().ClearTimer(HealthTickDelegate);
	}
}

//---------------------------------

void APlayerCharacter2D::HandleAirMovement(UCharacterMovementComponent* CMC)
{
	if(MovementState == EMoveState::MOVE_Air)
	{
		ToggleGravity(true);
		
		/* If in range and we press forward direction. Change State*/
		if(WallDetectorComponentForward->IsDetectingWall(this))
		{
			// Are we pressing in forward direction , which means we are clinging to the wall
			const float& DistanceToWall = WallDetectorComponentForward->DetectedWallDistance;
			if (DistanceToWall < WallHangDistance && (CMC->GetLastInputVector().X > 0.f || CMC->GetLastInputVector().X < 0.f))
			{
				MovementState = EMoveState::MOVE_Wall;
				
				// Stop Player from traversing in last Z Direction
				CMC->Velocity = FVector::Zero();
			}
		}

	}
}

//---------------------------------

void APlayerCharacter2D::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(UCharacterMovementComponent* CMC = GetCharacterMovement())
	{
		/*
		GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::Red,
			CMC->GetLastUpdateVelocity().ToString());
		*/
	
		if (CMC->IsMovingOnGround())
		{
			MovementState = EMoveState::MOVE_Ground;
		}
		else if(!CMC->IsMovingOnGround() && CMC->GetLastUpdateVelocity().Z < 0.f)		// Grab Wall only when falling
		{
			MovementState = EMoveState::MOVE_Air;
		}

		HandleAirMovement(CMC);

		if(GetWorldTimerManager().GetTimerRemaining(DashTimerDelegate) > 0.f)
		{
			const float TimeRemaining = GetWorldTimerManager().GetTimerRemaining(DashTimerDelegate);
			const float MaxValue = PlayerHudWidget->DashProgressBar->GetPercent();
			const float Percent = FMath::Clamp(TimeRemaining / MaxValue, 0.f, 1.f);

			PlayerHudWidget->DashProgressBar->SetPercent(Percent);
			PlayerHudWidget->SetDashCoolDown(Percent);
		}
	}
}

//---------------------------------

void APlayerCharacter2D::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInput = static_cast<UEnhancedInputComponent*>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacter2D::Move);
		EnhancedInput->BindAction(IA_Move, ETriggerEvent::Completed, this, &APlayerCharacter2D::MoveCompleted);
		
		EnhancedInput->BindAction(IA_Jump, ETriggerEvent::Started,this, &APlayerCharacter2D::StartJump);
		EnhancedInput->BindAction(IA_Jump, ETriggerEvent::Completed, this, &APlayerCharacter2D::StopJump);
		
		EnhancedInput->BindAction(IA_Attack, ETriggerEvent::Started, this, &APlayerCharacter2D::Attack);

		EnhancedInput->BindAction(IA_Dash, ETriggerEvent::Started, this, &APlayerCharacter2D::Dash);
	}
}

//---------------------------------

void APlayerCharacter2D::OnAttackCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		AEnemy* Enemy = static_cast<AEnemy*>(OtherActor);
		if(Enemy && Enemy->bIsAlive)
		{
			FRadialDamageEvent RadialDamageEvent;
			RadialDamageEvent.Origin = Enemy->GetActorLocation();
			RadialDamageEvent.Params = FRadialDamageParams(10, 3, 10, 3, 1.f);

			FHitResult HitResult;
			FPointDamageEvent PointDamageEvent;
			PointDamageEvent.Damage  = 10.f;
			PointDamageEvent.HitInfo = HitResult;
			PointDamageEvent.ShotDirection = GetActorForwardVector();
			PointDamageEvent.DamageTypeClass = nullptr;
			
			Enemy->TakeDamage(
				10.f,
				PointDamageEvent,
				GetController(),
				this
			);
		}
	}
}

//---------------------------------

float APlayerCharacter2D::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
											AController* EventInstigator,AActor* DamageCauser)
{
	if(bIsImmortal || !bIsAlive)
	{
		return 0;
	}
	
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	LastHealth = Health;
	if(Health - ActualDamage > 0.f)
	{
		Health -= ActualDamage;
		GetAnimInstance()->JumpToNode(FName("JumpTakeDmg"));

		bIsStunned = true;
		
		GetWorldTimerManager().SetTimer(StunTimerDelegate, this,
			&APlayerCharacter2D::OnStunTimerTimeOut,
			StunDuration,
			false
		);
	}
	else
	{
		bIsAlive = false;
		bCanAttack = false;

		GetAnimInstance()->JumpToNode(FName("JumpRemoval"));
		Health = 0.f;
		LastHealth = 0.f;
	}

	// Set Instant Damage
	const float Percent = FMath::Clamp(Health / 100.f, 0.f, 1.f);
	PlayerHudWidget->HealthProgressBarInstant->SetPercent(Percent);
	PlayerHudWidget->SetHealth(Health);

	// Set Delayed Damage
	GetWorldTimerManager().SetTimer(HealthTickDelegate, this, &APlayerCharacter2D::OnHealthTickTimeout,
											1.f, true, HealthTickRate);
	
	return ActualDamage;
}

//---------------------------------
