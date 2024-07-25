// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "PlayerCharacter2D.h"
#include "GameFramework/CharacterMovementComponent.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerDetectorSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Player Detector"));
	PlayerDetectorSphere->SetupAttachment(RootComponent);
	PlayerDetectorSphere->SetGenerateOverlapEvents(true);
}

//---------------------------------

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	PlayerDetectorSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
	PlayerDetectorSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnOverlapEnd);
}

//---------------------------------

void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(AEnemy* Enemy = Cast<AEnemy>(OtherActor))
	{
		return;
	}
	
	if(APlayerCharacter2D* Player = static_cast<APlayerCharacter2D*>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::White, TEXT("overlapping other: %s"), *Player->GetName());
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
		GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::White, TEXT("overlapping end"));
		if(PlayerTarget)
		{
			PlayerTarget = nullptr;
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
	const float VerticalDistanceTo = PlayerTarget->GetActorLocation().Z - GetActorLocation().Z;		
	if(VerticalDistanceTo > JumpThreshold)
	{
		//GEngine->AddOnScreenDebugMessage(-1, .1f, FColor::Blue, FString::Printf(TEXT("Vertical Distance to: %f"), VerticalDistanceTo));
		Jump();
		if(JumpCurrentCount > 0)
		{
			GetCharacterMovement()->SetJumpAllowed(false);
			GetCharacterMovement()->AddImpulse(GetActorForwardVector() * JumpImpulse);
		}
	}
}

//---------------------------------

void AEnemy::OnJumpCoolDownTimerTimeout()
{
	GetCharacterMovement()->SetJumpAllowed(true);
}
	
//---------------------------------

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIsAlive && PlayerTarget)
	{
		if(bIsMovementAllowed && StoppingDistance < GetHorizontalDistanceTo(PlayerTarget))
		{
			MoveHorizontalTo(PlayerTarget);
		}
		else
		{
			if(GetVerticalDistanceTo(PlayerTarget) < StoppingDistance)
			{
				GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::Red,
					TEXT("Attacking!"));	
			}
		}

		if(GetCharacterMovement()->IsJumpAllowed())
		{
			JumpWithImpulse();
			GetWorldTimerManager().SetTimer(
				JumpCoolDownTimerHandle,
				this,
				&AEnemy::OnJumpCoolDownTimerTimeout,
				JumpTimer,
				false,
				JumpTimer
			);
		}
		
		UpdateDirection(PlayerTarget);
	}
}

//---------------------------------

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

