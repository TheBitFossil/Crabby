// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "PlayerCharacter2D.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerDetectorSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Player Detector"));
	PlayerDetectorSphere->SetupAttachment(RootComponent);
	PlayerDetectorSphere->InitSphereRadius(DetectionRange);
	PlayerDetectorSphere->SetGenerateOverlapEvents(true);
	PlayerDetectorSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlap);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	
}

void AEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
							int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(APlayerCharacter2D* Player = static_cast<APlayerCharacter2D*>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::White, TEXT("overlapping other: %s"), *Player->GetName());
		if(!PlayerTarget)
		{
			PlayerTarget = Player;
		}
	}
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PlayerTarget)
	{
		float ActionValue = 0.f;

		const FVector Location = GetActorLocation();
		const FVector PlayerLocation = PlayerTarget->GetActorLocation();
		const FVector Direction = (PlayerLocation - Location);

		const float DistanceToPlayer = FVector::Dist(Location, PlayerLocation);

		// Is Player behind or in Front

		
		if(StoppingDistance < DistanceToPlayer)
		{
			// Stop Moving
		}
		else
		{
			AddMovementInput(Direction, ActionValue);
		}
	}
}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

