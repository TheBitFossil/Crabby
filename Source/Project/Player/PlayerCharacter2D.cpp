// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter2D.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Project/Ai/Enemy.h"
#include "Project/Components/AnimationComboComponent.h"
#include "Project/Components/InputActionsComponent.h"
#include "Project/Components/ItemDetectorComponent.h"
#include "Project/Components/WallDetectorComponent.h"
#include "Project/Core/PlatformerGameInstance.h"


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
	InputActionsComponent = CreateDefaultSubobject<UInputActionsComponent>(TEXT("Input Actions Config"));
	AnimationComboComponent = CreateDefaultSubobject<UAnimationComboComponent>(TEXT("Animation Combo Handler"));
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

	if(!CMC)
	{
		CMC = GetCharacterMovement();
		CMC->GravityScale = CustomGravityScale;
	}

	// Init PlayerData
	GameInstance = Cast<UPlatformerGameInstance>(GetGameInstance());
	if(!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("No viable GameInstance found inside PlayerCharacter2D."));
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

void APlayerCharacter2D::Run(const FInputActionValue& InputActionValue)
{
	if(!CMC || !Controller || bIsStunned)
	{
		return;
	}
	
	if(AnimationComboComponent->GetAnimationState() == Running)
	{
		AnimationComboComponent->SetAnimationState(Walking);
		CMC->MaxWalkSpeed = WalkSpeed;
	}
	else if(AnimationComboComponent->GetAnimationState() == Walking)
	{
		AnimationComboComponent->SetAnimationState(Running);
		CMC->MaxWalkSpeed = RunSpeed;
	}
}

//---------------------------------

void APlayerCharacter2D::Dash(const FInputActionValue& InputActionValue)
{
	if(!CMC || !bCanDash)
	{
		return;
	}
	
	bCanDash = false;
	bIsImmortal = true;
	
	// Directly update PlayerData struct inside GameInstance 
	GameInstance->GetLastStaminaRef() = GameInstance->GetStamina();
	
	if(GameInstance->GetStamina() > StaminaCostDash)
	{
		AnimationComboComponent->SetAnimationState(Dashing);
		
		const FVector DashDirection = GetActorForwardVector();
		const float AirDashForce = DashForce / 2.f;
		if(CMC->IsMovingOnGround())
		{
			LaunchCharacter(DashDirection * DashForce, false, false);
		}
		else
		{
			// TODO:: Find a way to balance Force while in Air. Maybe Higher Gravity ? More Friction ?
			LaunchCharacter(DashDirection * AirDashForce / 10.f, false, false);
		}
				
		// Update Instant Stamina Bar
		GameInstance->RemoveStamina(StaminaCostDash);

		// Start Delayed Stamina Tick
		GetWorldTimerManager().SetTimer(
			StaminaTickDelegate,
			this,
			&APlayerCharacter2D::OnStaminaTickTimeOut,
			1.f,
			false,
			StaminaTickRate
		);

		// Set the Bar to Zero immediately after Dashing
		GameInstance->ResetDashBar();

		bIsImmortal = false;
		
		// Start update of the DashBar
		GetWorldTimerManager().SetTimer(
			DashTimerDelegate,
			this,
			&APlayerCharacter2D::OnDashTimerTimeOut,
			DashCoolDownTickRate,
			true,
			DashCoolDownTickRate
		);
	}
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

void APlayerCharacter2D::Crouching(const FInputActionValue& InputActionValue)
{
	if(AnimationComboComponent->GetAnimationState() == Crouched)
	{
		UnCrouch();
		AnimationComboComponent->SetAnimationState(Walking);
	}
	else if(AnimationComboComponent->GetAnimationState() == Walking)
	{
		Crouch();
		AnimationComboComponent->SetAnimationState(Crouched);
	}
}

//---------------------------------

void APlayerCharacter2D::Weapon(const FInputActionValue& InputActionValue)
{
	AnimationComboComponent->AttackCombo(EAnimationState::Sword);
}

//---------------------------------

void APlayerCharacter2D::Punch(const FInputActionValue& InputActionValue)
{
	if(!bIsAlive || bIsStunned || !AnimationComboComponent->CanAttack())
	{
		return;
	}

	AnimationComboComponent->AttackCombo(EAnimationState::Melee);
}

//---------------------------------

void APlayerCharacter2D::Kick(const FInputActionValue& InputActionValue)
{
	AnimationComboComponent->AttackCombo(EAnimationState::Kick);
}

//---------------------------------

void APlayerCharacter2D::Block(const FInputActionValue& InputActionValue)
{
	
}

//---------------------------------

void APlayerCharacter2D::Grab(const FInputActionValue& InputActionValue)
{
	
}

//---------------------------------

void APlayerCharacter2D::EquipBow(const FInputActionValue& InputActionValue)
{
	
		GetAnimInstance()->JumpToNode(FName("JumpBow"));
	
}

//---------------------------------

void APlayerCharacter2D::Aim(const FInputActionValue& InputActionValue)
{
	
}

//---------------------------------

void APlayerCharacter2D::ToggleGravity(const bool Enabled) const
{
	if(!CMC)
	{
		return;
	}
	
	if(Enabled)
	{
		CMC->GravityScale = CustomGravityScale;
	}
	else
	{
		CMC->GravityScale = WallJumpGravityScale;
	}
}

//---------------------------------
/* A Timer that counts to a specific max value. Shows progress on the HUD between 0 and 1 */
void APlayerCharacter2D::OnDashTimerTimeOut()
{
	const float& CoolDownTime = GameInstance->GetDashCoolDown();

	UE_LOG(LogTemp, Log, TEXT("CurrentDashTimer: %f, CoolDownTime: %f"), CurrentDashTimer, CoolDownTime);
	
	CurrentDashTimer += DashCoolDownTickAmount;
	if(CurrentDashTimer >= CoolDownTime)
	{
		CurrentDashTimer = 0.f;
		GetWorldTimerManager().ClearTimer(DashTimerDelegate);

		GameInstance->UpdateDashBar(GameInstance->GetDashCoolDown());

		bCanDash = true;
	}
	else
	{
		GameInstance->UpdateDashBar(CurrentDashTimer);
	}
}

//---------------------------------

void APlayerCharacter2D::OnStaminaRegenTimeOut()
{
	// ... add stamina regen when player picks up items
}

//---------------------------------

void APlayerCharacter2D::OnStaminaTickTimeOut()
{
	if (GameInstance)
	{
		UpdateAttributeTick(
		GameInstance->GetLastStaminaRef(),
		GameInstance->GetStamina(),
		StaminaCostDash,
		StaminaRemovePerTick,
		StaminaTickDelegate,
		"Stamina",
		[this](float NewValue){GameInstance->StaminaDelayed(NewValue);},
		StaminaTickRate
		);
	}
}

//---------------------------------

void APlayerCharacter2D::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if(MovementState != EMoveState::MOVE_Ground)
	{
		MovementState = EMoveState::MOVE_Ground;
		UE_LOG(LogTemp, Warning, TEXT("Landed->"));
	}
}

//---------------------------------

void APlayerCharacter2D::WallJump()
{
	if(MovementState != EMoveState::MOVE_Wall || !CMC)
	{
		return;
	}

	const FVector DirNormal = (-GetActorForwardVector() + GetActorUpVector()).GetSafeNormal();
	const FVector JumpDirection = DirNormal * WallJumpForce;

	ToggleGravity(false);
	LaunchCharacter(JumpDirection, false, false);	// Get some distance from the Wall

	GetWorldTimerManager().SetTimer(
		WallJumpTimerDelegate,
		this,
		&APlayerCharacter2D::OnWallJumpTimerTimeOut,
		WallJumpCustomGravityDuration,
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

	OnIsAttackAllowed(true);
	OnIsMovementAllowed(true);
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

/**
 * Used for updating the delayed Progress Bars
 * @param Last : Pass by Ref, this Value changes each Tick.
 * @param Current: Lowest possible Value for Last.
 * @param TotalAmount: Reducing this much from Last to Current
 * @param RemovalPerTick: How much to remove each tick in fixed %
 * @param AttributeName: Identification and debugging
 * @param UpdateRefFunction: Lambda Function that will update the first Parameter ref inside GameInstance
 */
void APlayerCharacter2D::UpdateAttributeTick(float& Last, const float& Current, const float& TotalAmount, const float& RemovalPerTick,
	FTimerHandle& TimerHandle, const FString& AttributeName, TFunction<void(float)>UpdateRefFunction, float TickRate)
{
	// Calculate Removal per Tick
	const float Percentage = (RemovalPerTick / 100.f);
	const float AmountToRemove = TotalAmount * Percentage;

	// Debug Logging
	UE_LOG(LogTemp, Log, TEXT("%s Tick -> Percentage(%f), AmountToRemove(%f), LastValue(%f)"), *AttributeName, Percentage, AmountToRemove, Last);

	// Slowly remove the attribute until we reach the current value
	if(Last > Current)
	{
		float NewValue = Last - AmountToRemove;
		if(NewValue < Current)
		{
			NewValue = Current;
		}

		// Debug logging
		UE_LOG(LogTemp, Log, TEXT("%s Value Ref Update to(%f)"), *AttributeName, NewValue);
		UpdateRefFunction(NewValue);

		// Set for next Tick
		Last = NewValue;

		// Stop Timer if we've reached the target value
		if(Last < Current)
		{
			GetWorldTimerManager().ClearTimer(TimerHandle);
		}
		else
		{
			GetWorldTimerManager().SetTimer(
				TimerHandle,
				FTimerDelegate::CreateLambda
				(
					[this, &Last, Current, TotalAmount, RemovalPerTick, &TimerHandle, AttributeName, UpdateRefFunction, TickRate]()
					{UpdateAttributeTick(Last, Current, TotalAmount, RemovalPerTick, TimerHandle, AttributeName, UpdateRefFunction, TickRate);}
				),
				TickRate,
				false);
		}
	}
	else
	{
		// Stop Timer if we've reached the target value
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

//---------------------------------

void APlayerCharacter2D::OnHealthTickTimeOut()
{
	if(GameInstance)
	{
		UpdateAttributeTick(
			GameInstance->GetLastHealthRef(),
			GameInstance->GetHealth(),
			GameInstance->GetDamageTaken(),
			HealthRemovePerTick,
			HealthTickDelegate,
			"Health",
			[this](float NewValue){GameInstance->HealthDelayed(NewValue);},
			HealthTickRate
		);
	}
}

//---------------------------------

void APlayerCharacter2D::HandleAirMovement(UCharacterMovementComponent* CharacterMovement)
{
	if(MovementState == EMoveState::MOVE_Air && AnimationComboComponent->GetAnimationState() != Dashing)
	{
		ToggleGravity(true);
		
		/* If in range of a WorldStatic and we press forward direction. Change State*/
		if(WallDetectorFront->IsDetectingWall(this))
		{
			// Are we pressing in forward direction , which means we are clinging to the wall
			const float& DistanceToWall = WallDetectorFront->DetectedWallDistance;
			if (DistanceToWall < WallHangDistance && (CharacterMovement->GetLastInputVector().X > 0.f || CharacterMovement->GetLastInputVector().X < 0.f))
			{
				MovementState = EMoveState::MOVE_Wall;
				
				// Stop Player from traversing in last (Z) Direction
				CharacterMovement->Velocity = FVector::Zero();
			}
		}
	}
}

//---------------------------------

void APlayerCharacter2D::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(CMC)
	{
		if (CMC->IsMovingOnGround())
		{
			MovementState = EMoveState::MOVE_Ground;
		}
		else if(!CMC->IsMovingOnGround() && CMC->GetLastUpdateVelocity().Z < 0.f)		// Grab Wall only when falling
		{
			MovementState = EMoveState::MOVE_Air;
		}

		HandleAirMovement(CMC);
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
			//TODO:: Make IDamageable
			// We have Hit a viable Target Start ComboWindow
			AnimationComboComponent->SetHasHit(true);
			AnimationComboComponent->StartComboWindowTimer();
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
	
	// Directly update PlayerData struct inside GameInstance
	GameInstance->GetLastHealthRef() = GameInstance->GetHealth();
	GameInstance->SetDamageTaken(ActualDamage);
	
	const float HealthLeft = GameInstance->GetHealth() - ActualDamage;
	if(HealthLeft > 0.f)
	{
		// Update: Instant HP Bar
		GameInstance->RemoveHealthInstant(ActualDamage);
		
		GetAnimInstance()->JumpToNode(FName("JumpHurt"));

		bIsStunned = true;
		
		GetWorldTimerManager().SetTimer(
			StunTimerDelegate,
			this,
			&APlayerCharacter2D::OnStunTimerTimeOut,
			StunDuration,
			false
		);

		// Start Delayed Damage Tick
		GetWorldTimerManager().SetTimer(
			HealthTickDelegate,
			this,
			&APlayerCharacter2D::OnHealthTickTimeOut,
			1.f,
			false,
			HealthTickRate
		);
		UE_LOG(LogTemp, Warning, TEXT("Starting Delayed Damage TickRate(%f)"), HealthTickRate);
	}
	else
	{
		HealthDepleted();
	}
		
	return ActualDamage;
}

//---------------------------------

void APlayerCharacter2D::HealthDepleted()
{
	bIsAlive = false;
	OnIsAttackAllowed(false);
	OnIsMovementAllowed(false);
	
	GetAnimInstance()->JumpToNode(FName("JumpRemoval"));

	GameInstance->SetHealth(0.f);
	GameInstance->GetLastHealthRef() = 0.f;
}

//---------------------------------

void APlayerCharacter2D::OnAnimNotifyDashEnded()
{
	// Callback from UAnimNotifyState_Dashing::OnNotifyEnd
	AnimationComboComponent->SetAnimationState(Walking);
}

//---------------------------------
/* Is called within this and from Animation Notifies */
void APlayerCharacter2D::OnIsMovementAllowed(const bool bIsActive)
{
	bIsMovementAllowed = bIsActive;
}

//---------------------------------

void APlayerCharacter2D::OnIsAttackAllowed(const bool bIsActive)
{
	bCanAttack = bIsActive;
}