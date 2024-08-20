// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Project/Player/PlayerCharacter2D.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerDetectorSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Player Detector"));
	PlayerDetectorSphere->SetupAttachment(RootComponent);
	PlayerDetectorSphere->SetGenerateOverlapEvents(true);

	AttackCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Attack Collision Detection"));
	AttackCollisionBox->SetupAttachment(RootComponent);
	AttackCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnAttackCollisionOverlapBegin);

	HealthDisplay = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Health Display"));
	HealthDisplay->SetupAttachment(RootComponent);
}

//---------------------------------

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	PlayerDetectorSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
	PlayerDetectorSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnOverlapEnd);

	OnAttackAnimationOverrideDelegate.BindUObject(this, &AEnemy::OnAttackSequenceEnd);
	ToggleAttackCollisionBox(false);

	HealthDisplay->bHiddenInGame = true;
	UpdateHealth(Health);
}

//---------------------------------

void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(AEnemy* Enemy = Cast<AEnemy>(OtherActor))
	{
		return;
	}
	if(!bIsHostile)
	{
		return;
	}
	if(APlayerCharacter2D* Player = Cast<APlayerCharacter2D>(OtherActor))
	{
		//GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::White, TEXT("overlapping other: %s"), *Player->GetName());
		if(!PlayerTarget)
		{
			PlayerTarget = Player;
		}
	}
}

//---------------------------------

void AEnemy::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(APlayerCharacter2D* Player = static_cast<APlayerCharacter2D*>(OtherActor))
	{
		//GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::White, TEXT("overlapping end"));
		if(PlayerTarget)
		{
			PlayerTarget = nullptr;
		}
	}
}

//---------------------------------

void AEnemy::UpdateHealth(int NewHealth)
{
	if(!HealthDisplay)
	{
		return;
	}
	
	const FString Msg = FString::Printf(TEXT("Health: %d"), NewHealth);
	const FText Display = FText::FromString(Msg);
	
	HealthDisplay->SetText(Display);
}

//---------------------------------

void AEnemy::Stun(const float DurationInSeconds)
{
	bIsStunned = true;

	const bool IsTimerActive = GetWorldTimerManager().IsTimerActive(StunTimerHandle);
	if(IsTimerActive)
	{
		GetWorldTimerManager().ClearTimer(StunTimerHandle);
	}
	
	GetWorldTimerManager().SetTimer(StunTimerHandle, this,
		&AEnemy::OnStunTimerTimeOut,
		1.f,
		false,
		DurationInSeconds
	);

	/* If we are attacked, we need to cancel. */ 
	GetAnimInstance()->StopAllAnimationOverrides();
}

//---------------------------------

void AEnemy::OnStunTimerTimeOut()
{
	bIsStunned = false;
}

//---------------------------------

void AEnemy::OnAttackCollisionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		APlayerCharacter2D* Player = Cast<APlayerCharacter2D>(OtherActor);
		if(Player && Player->bIsAlive)
		{
			FHitResult HitResult;
			FPointDamageEvent PointDamageEvent;
			PointDamageEvent.DamageTypeClass = UDamageType::StaticClass();
			PointDamageEvent.Damage = AttackDmg;
			PointDamageEvent.HitInfo = HitResult;
			PointDamageEvent.ShotDirection = GetActorForwardVector();
			
			Player->TakeDamage(
				AttackDmg,
				PointDamageEvent,
				GetController(),
				this
			);
		}
	}
}

//---------------------------------

void AEnemy::MoveHorizontalTo(const APlayerCharacter2D* Target)
{
	const FVector DirNormal = (Target->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	AddMovementInput(DirNormal, 1);
}

//---------------------------------

void AEnemy::UpdateDirection(const APlayerCharacter2D* Target)
{
	const FVector DirNormal = (Target->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	const FRotator CurrentRotation = GetController()->GetControlRotation();
	
	if(DirNormal.X < 0.f)
	{
		if (CurrentRotation.Yaw != 180.0f)
		{
			SetActorRotation(FRotator(CurrentRotation.Pitch, 180.0f, CurrentRotation.Roll));
		}
	}
	else if(DirNormal.X > 0.f)
	{
		if (CurrentRotation.Yaw != 0.0f)
		{
			SetActorRotation(FRotator(CurrentRotation.Pitch, 0.0f, CurrentRotation.Roll));
		}
	}
}

/* If player is above and too far away jump.  */
void AEnemy::JumpWithImpulse()
{
	Jump();
	GetCharacterMovement()->AddImpulse(GetActorForwardVector() + JumpImpulse);
}

//---------------------------------

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	HealthDisplay->bHiddenInGame = false;
	UpdateHealth(Health);
	
	if(Health - ActualDamage > 0.f)
	{
		Health -= ActualDamage;
		// A. send from caller or B. fixed inside the enemy depending on damage
		Stun(.3f);
		GetAnimInstance()->JumpToNode(FName("JumpHit"));
	}
	else
	{
		bIsAlive = false;
		bCanAttack = false;
		
		Health = 0.f;
		HealthDisplay->bHiddenInGame = true;

		GetAnimInstance()->JumpToNode(FName("JumpRemoval"), FName("Locomotion"));
	}
	
	return ActualDamage;
}

//---------------------------------

void AEnemy::OnJumpCoolDownTimerTimeOut()
{
	GetCharacterMovement()->SetJumpAllowed(true);
}
	
//---------------------------------

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIsAlive && PlayerTarget && !bIsStunned)
	{
		if(bIsMovementAllowed && StoppingDistance < GetHorizontalDistanceTo(PlayerTarget))
		{
			const float HorizontalDistance = GetHorizontalDistanceTo(PlayerTarget);
			const float VerticalDistance = GetVerticalDistanceTo(PlayerTarget);

			bool bIsCloseEnoughHorizontalToAttack = HorizontalDistance <= AttackHorizontalThreshold;
			bool bIsCloseEnoughVerticalToAttack = VerticalDistance <= AttackVerticalThreshold;
			
			if(bIsCloseEnoughHorizontalToAttack && bIsCloseEnoughVerticalToAttack)
			{
				if(PlayerTarget && PlayerTarget->bIsAlive)
				{
					Attack();
				}
			}
			else
			{
				if(HorizontalDistance > AttackHorizontalThreshold)
				{
					MoveHorizontalTo(PlayerTarget);
				}

				if(VerticalDistance > JumpThreshold && GetCharacterMovement()->IsMovingOnGround())
				{
					JumpWithImpulse();
				}
			}
		}
		
		UpdateDirection(PlayerTarget);
	}
}

//---------------------------------

void AEnemy::Attack()
{
	if(bCanAttack && bIsAlive && !bIsStunned)
	{
		bCanAttack = false;
		
		GetAnimInstance()->PlayAnimationOverride(
			AttackAnimationSequence,
			FName("DefaultSlot"),
			1.f,
			0.f,
			OnAttackAnimationOverrideDelegate
		);

		GetWorldTimerManager().SetTimer(
			AttackCooldownTimer,
			this,
			&AEnemy::OnAttackCoolDownTimerTimeOut,
			AttackCooldownTime,
			false,
			AttackCooldownTime
		);
	}
}

//---------------------------------

void AEnemy::ToggleAttackCollisionBox(bool Enabled)
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

void AEnemy::OnAttackCoolDownTimerTimeOut()
{
	if(bIsAlive)
	{
		bCanAttack = true;
	}
}

//---------------------------------

void AEnemy::OnAttackSequenceEnd(bool Completed)
{
	// Empty
}
