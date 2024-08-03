// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter2D.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ProgressBar.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Project/Ai/Enemy.h"
#include "Project/Components/ItemDetectorComponent.h"
#include "Project/Components/WallDetectorComponent.h"
#include "Project/Core/PlatformerGameInstance.h"
#include "Project/UI/PlayerHUD.h"


APlayerCharacter2D::APlayerCharacter2D()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	AttackCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Attack Collision Detector"));
	AttackCollisionBox->SetupAttachment(RootComponent);

	ItemDetectorComponent = CreateDefaultSubobject<UItemDetectorComponent>(TEXT("Item Detector"));
	WallDetectorFront = CreateDefaultSubobject<UWallDetectorComponent>(TEXT("Wall Detector"));
}

//---------------------------------

void APlayerCharacter2D::BeginPlay()
{
	Super::BeginPlay();

	if(APlayerController* PC = Cast<APlayerController>(Controller))
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
	ToggleAttackCollisionBox(false);
	
	GetCharacterMovement()->GravityScale = CustomGravityScale;

	GameInstance = Cast<UPlatformerGameInstance>(GetGameInstance());

	InitUserInterface();
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
	UCharacterMovementComponent* CMC = GetCharacterMovement();
	if(!CMC || !bCanDash)
	{
		return;
	}

	const FVector DashDirection = GetActorForwardVector();
	const float AirDashForce = DashForce / 2.f;
	if(CMC->IsMovingOnGround())
	{
		LaunchCharacter(DashDirection * DashForce, true, true);
	}
	else
	{
		// TODO:: Find a way to balance Force while in Air. Maybe Higher Gravity ? More Friction ?
		LaunchCharacter(DashDirection * AirDashForce, true, true);
	}
	
	bCanDash = false;
	bIsImmortal = true;

	// Set the Bar to Zero immediately after Dashing
	PlayerHudWidget->DashProgressBar->SetPercent(0.f);
	PlayerHudWidget->SetDashCoolDown(0.f);
	
	GetWorldTimerManager().SetTimer(DashTimerDelegate,
		this,
		&APlayerCharacter2D::OnDashTimerTimeOut,
		1.f,
		false,
		GameInstance->PlayerData.DashCoolDown
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

void APlayerCharacter2D::EquipSlot(const FInputActionValue& InputActionValue)
{
	bEquippedSlot01 = !bEquippedSlot01;
	if(bEquippedSlot01)
	{
		GetAnimInstance()->JumpToNode(FName("JumpBow_01"));
	}
}

//---------------------------------

void APlayerCharacter2D::BowDraw(const FInputActionValue& InputActionValue)
{
	if(bEquippedSlot01)
	{
		
	}
}

//---------------------------------
/*
 * Used for ProgressBars to fit Values bigger than 1
 */
float APlayerCharacter2D::NormalizeValue(const float& CurrentValue, const float& MaxValue)
{
	return FMath::Clamp(CurrentValue / MaxValue, 0.f, 1.f);
}

//---------------------------------

void APlayerCharacter2D::OnDashTimerTimeOut()
{
	bCanDash = true;
	bIsImmortal = false;
	
	PlayerHudWidget->SetDashCoolDown(GameInstance->PlayerData.DashCoolDown);
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
	if(GameInstance)
	{
		// Calculate the damage to remove per tick as a percentage of the initial damage
		const float DamagePerTick = DamageTaken * (HealthRemovePerTick / 100.f);

		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow,
			FString::Printf(TEXT("DMG: %f"), DamagePerTick));
		

		// Slowly remove HP delayed until we reach current HP
		if(LastHealth > GameInstance->PlayerData.HP)
		{
			float HP = LastHealth - DamagePerTick;
			if(HP < GameInstance->PlayerData.HP)
			{
				HP = GameInstance->PlayerData.HP;
			}

			// Fit the current HP inside the Progress-Bar
			const float Percent = NormalizeValue(HP, GameInstance->PlayerData.MaxHP);
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow,
				FString::Printf(TEXT("HP: %f"), Percent));
			
			UpdateHPDelayed(Percent);
			// As Text
			PlayerHudWidget->SetHealth(HP);

			// Set HP for next Tick
			LastHealth = HP;

			// Stop Timer early if we already reached the Value
			if(LastHealth <= GameInstance->PlayerData.HP)
			{
				GetWorldTimerManager().ClearTimer(HealthTickDelegate);
			}
			
			GetWorldTimerManager().SetTimer(HealthTickDelegate, this, &APlayerCharacter2D::OnHealthTickTimeout,
													1.f, false, HealthTickRate);
		}
		else
		{
			GetWorldTimerManager().ClearTimer(HealthTickDelegate);
		}
	}
}

//---------------------------------

void APlayerCharacter2D::HandleAirMovement(UCharacterMovementComponent* CMC)
{
	if(MovementState == EMoveState::MOVE_Air)
	{
		ToggleGravity(true);
		
		/* If in range and we press forward direction. Change State*/
		if(WallDetectorFront->IsDetectingWall(this))
		{
			// Are we pressing in forward direction , which means we are clinging to the wall
			const float& DistanceToWall = WallDetectorFront->DetectedWallDistance;
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

void APlayerCharacter2D::UpdateDashBar(float Val)
{
	if(GetWorldTimerManager().GetTimerRemaining(DashTimerDelegate) > 0.f)
	{
		const float TimeRemaining = GetWorldTimerManager().GetTimerRemaining(DashTimerDelegate);
		const float NormalizedValue = NormalizeValue(TimeRemaining, Val);

		PlayerHudWidget->DashProgressBar->SetPercent(NormalizedValue);
	}
	else
	{
		PlayerHudWidget->DashProgressBar->SetPercent(Val);
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

		UpdateDashBar(GameInstance->PlayerData.DashCoolDown);
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

		EnhancedInput->BindAction(IA_Equip_Slot_01, ETriggerEvent::Started, this, &APlayerCharacter2D::EquipSlot);

		EnhancedInput->BindAction(IA_Bow_Draw, ETriggerEvent::Started, this, &APlayerCharacter2D::BowDraw);
		EnhancedInput->BindAction(IA_Bow_Draw, ETriggerEvent::Completed, this, &APlayerCharacter2D::BowDraw);
	}
}

//---------------------------------

void APlayerCharacter2D::OnAttackCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		AEnemy* Enemy = Cast<AEnemy>(OtherActor);
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

	// Cache this for the delayed HealthBar. Get the Value from GameInstance
	LastHealth = GameInstance->PlayerData.HP;
	DamageTaken = ActualDamage;
	
	const float HealthLeft = GameInstance->PlayerData.HP - ActualDamage;
	if(HealthLeft > 0.f)
	{
		GameInstance->RemoveHealth(ActualDamage);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("GI HP: %f"), GameInstance->PlayerData.HP));
		
		GetAnimInstance()->JumpToNode(FName("JumpTakeDmg"));

		bIsStunned = true;
		
		GetWorldTimerManager().SetTimer(
			StunTimerDelegate,
			this,
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

		GameInstance->SetHP(0.f);
		LastHealth = 0.f;
	}

	// Update the Instant Damage HP Bar
	const float Percent = NormalizeValue(GameInstance->PlayerData.HP, GameInstance->PlayerData.MaxHP);
	UpdateHPInstant(Percent);

	// Start Delayed Damage Tick
	GetWorldTimerManager().SetTimer(
		HealthTickDelegate,
		this,
		&APlayerCharacter2D::OnHealthTickTimeout,
		1.f,
		false,
		HealthTickRate
	);
	
	return ActualDamage;
}

//---------------------------------

void APlayerCharacter2D::InitUserInterface()
{
	if(PlayerHudClass)
	{
		PlayerHudWidget = CreateWidget<UPlayerHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0), PlayerHudClass);
		if(PlayerHudWidget && GameInstance)
		{
			PlayerHudWidget->AddToPlayerScreen();
			PlayerHudWidget->SetLevel(909);

			// As Percentage
			const float PercentHealth = NormalizeValue(GameInstance->PlayerData.HP, GameInstance->PlayerData.MaxHP);
			UpdateHPInstant(PercentHealth);
			UpdateHPDelayed(PercentHealth);

			const float PercentStamina = NormalizeValue(GameInstance->PlayerData.DashCoolDown, GameInstance->PlayerData.DashCoolDown);
			UpdateDashBar(PercentStamina);

			// As Text
			PlayerHudWidget->SetHealth(GameInstance->PlayerData.HP);
			
			UpdateStamina(GameInstance->PlayerData.Stamina);
			UpdateDashCoolDown(GameInstance->PlayerData.DashCoolDown);
			UpdateCredits(GameInstance->PlayerData.Credits);
		}
	}
}

//---------------------------------

void APlayerCharacter2D::UpdateHPInstant(float Val)
{
	PlayerHudWidget->HealthProgressBarInstant->SetPercent(Val);
}

//---------------------------------

void APlayerCharacter2D::UpdateHPDelayed(float Val)
{
	// As Progress Bar
	PlayerHudWidget->HealthProgressBarDelayed->SetPercent(Val);
}

//---------------------------------

void APlayerCharacter2D::UpdateStamina(float Val)
{
	// TODO:: Implement Stamina which gets used by dashing.
	PlayerHudWidget->SetStamina(Val);
}

//---------------------------------

void APlayerCharacter2D::UpdateCredits(int32 Val)
{
	PlayerHudWidget->SetDiamonds(Val);
}

//---------------------------------

void APlayerCharacter2D::UpdateDashCoolDown(float Val)
{
	PlayerHudWidget->SetDashCoolDown(Val);
}



