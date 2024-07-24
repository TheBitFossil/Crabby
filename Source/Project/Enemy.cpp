// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "PlayerCharacter2D.h"


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

void AEnemy::MoveTowards(const APlayerCharacter2D* Target)
{
	// Movement
	const FVector Location = GetActorLocation();
	const FVector PlayerLocation = Target->GetActorLocation();
		
	const FVector Direction = (PlayerLocation - Location);
	const FVector DirNormal = Direction.GetSafeNormal();

	// Distance Checking
	const float DistanceToPlayer = FVector::Dist(Location, PlayerLocation);
	if(StoppingDistance < DistanceToPlayer)
	{
		AddMovementInput(DirNormal, 1);
	}
}
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PlayerTarget)
	{
		MoveTowards(PlayerTarget);
		
		// Direction Facing
		const float Dot = GetDotProductTo(PlayerTarget);
		FString MSG = FString::Printf(TEXT("Dot %f"), Dot);
		GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::White, MSG);

		const FRotator CurrentRotation = GetController()->GetControlRotation();
		
		if(Dot < 0.f) // behind
		{
			
		}
		else if(Dot > 0.f) // in front
		{
			
		}
	}
}

//---------------------------------

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

