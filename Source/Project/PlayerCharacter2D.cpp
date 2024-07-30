// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter2D.h"

#include "Enemy.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WallDetectorComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


APlayerCharacter2D::APlayerCharacter2D()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent->SetUsingAbsoluteRotation(true);
	
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
}

//---------------------------------

void APlayerCharacter2D::SetDirectionFacing(const float ActionValue)
{
	if(!Controller)
	{
		return;
	}
	
	const FRotator CurrentRotation = GetCurrentRotation();
	
	if(ActionValue < 0.f)
	{
		if(!FMath::IsNearlyEqual(CurrentRotation.Yaw, 180.f, 1.f))
		{
			FRotator NewRotation = FRotator(CurrentRotation.Pitch, 180.f, CurrentRotation.Roll);
			Controller->SetControlRotation(NewRotation);
			//SetActorRotation(NewRotation);
		}
	}
	else if(ActionValue > 0.f)
	{
		if(!FMath::IsNearlyEqual(CurrentRotation.Yaw, 0.f, 1.f))
		{
			FRotator NewRotation = FRotator(CurrentRotation.Pitch, 0.f, CurrentRotation.Roll);
			Controller->SetControlRotation(NewRotation);
			//SetActorRotation(NewRotation);
		}
	}
}

//---------------------------------

void APlayerCharacter2D::Move(const FInputActionValue& InputActionValue)
{
	if(!Controller || bIsStunned)
	{
		return;
	}
	
	const float ActionValue = InputActionValue.Get<float>();

	CurrentMovementInput = ActionValue;
	
	if(bIsAlive && bIsMovementAllowed)
	{
		const FVector Direction = FVector(1.f, 0.f, 0.f); 
		AddMovementInput(Direction, ActionValue);
		SetDirectionFacing(ActionValue);
	}
}

//---------------------------------

void APlayerCharacter2D::StartJump(const FInputActionValue& InputActionValue)
{
	if(!bIsAlive)
	{
		return;
	}

	switch (MovementState)
	{
	case EMoveState::MOVE_Ground:
		Jump();
		break;
	case EMoveState::MOVE_Air:
		// Double Jump
		break;
	case EMoveState::Move_Wall:
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
	if(!bIsAlive)
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
	
	GetWorldTimerManager().SetTimer(DashTimerDelegateHandle,
		this,
		&APlayerCharacter2D::OnDashTimerTimeOut,
		1.f,
		false,
		DashCooldownTime
	);
}

//---------------------------------

void APlayerCharacter2D::OnDashTimerTimeOut()
{
	bCanDash = true;
	bIsImmortal = false;
}

//---------------------------------

void APlayerCharacter2D::Falling()
{
	Super::Falling();

}

//---------------------------------

void APlayerCharacter2D::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	bCanWallJump = false;

	if(UCharacterMovementComponent* CMC = GetCharacterMovement())
	{
		if(CMC->GravityScale != CustomGravityScale)
		{
			CMC->GravityScale = CustomGravityScale;
		}
	}
}

//---------------------------------

void APlayerCharacter2D::WallJump()
{
	if(!bCanWallJump)
	{
		return;
	}
	
	bCanWallJump = false;
	const FVector BackwardDirection = -GetActorForwardVector();
	const FVector UpwardDirection = GetActorUpVector();
	
	const FVector JumpDirection = (BackwardDirection + UpwardDirection) * WallJumpForce;

	if(UCharacterMovementComponent* CMC = GetCharacterMovement())
	{
		CMC->GravityScale = CustomGravityScale;
		LaunchCharacter(JumpDirection, true, true);
	}
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
	if(UCharacterMovementComponent* CMC = GetCharacterMovement())
	{
		CMC->GravityScale = CustomGravityScale;
		bCanWallJump = false;
	}
}

//---------------------------------

void APlayerCharacter2D::OnStunTimerTimeOut()
{
	bIsStunned = false;
}

//---------------------------------

void APlayerCharacter2D::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(UCharacterMovementComponent* CMC = GetCharacterMovement())
	{
		if (CMC->IsMovingOnGround())
		{
			MovementState = EMoveState::MOVE_Ground;
		}
		else if(!CMC->IsMovingOnGround() && CMC->GetLastUpdateVelocity().Z > 0.f)
		{
			MovementState = EMoveState::MOVE_Air;
		}
	}

	if(MovementState == EMoveState::MOVE_Air)
	{
		/* We need to check if there is a wall in Range before next call */
		if(WallDetectorComponentForward->IsDetectingWall(WallHangRange, this))
		{
			/* If its in range and we press forward direction. Change State*/
			if(WallDetectorComponentForward->CanWallHang() && CurrentMovementInput > 0.f)
			{
				MovementState = EMoveState::Move_Wall;
			}
			else
			{
				/* Go back to Air mode, when we release the Input */
				MovementState = EMoveState::MOVE_Air;
			}
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

float APlayerCharacter2D::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if(bIsImmortal || !bIsAlive)
	{
		return 0;
	}
	
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if(Health - ActualDamage > 0.f)
	{
		Health -= ActualDamage;
		GetAnimInstance()->JumpToNode(FName("JumpTakeDmg"));

		bIsStunned = true;
		GetWorldTimerManager().SetTimer(StunTimerHandle, this, &APlayerCharacter2D::OnStunTimerTimeOut, StunDuration, false);
	}
	else
	{
		bIsAlive = false;
		bCanAttack = false;

		GetAnimInstance()->JumpToNode(FName("JumpRemoval"));
		Health = 0.f;
	}

	return ActualDamage;
}

//---------------------------------
