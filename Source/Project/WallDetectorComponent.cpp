// Fill out your copyright notice in the Description page of Project Settings.


#include "WallDetectorComponent.h"


UWallDetectorComponent::UWallDetectorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWallDetectorComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UWallDetectorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Check for collisions
	
	// Return true if it's a Wall
	
}

//---------------------------------

bool UWallDetectorComponent::IsDetectingWall(const float& WallHangRange, const AActor* IgnoredActor = nullptr)
{
	if(!WallHangRange)
	{
		return false;
	}

	const FVector StartLocation = GetComponentLocation();
	const FVector End = StartLocation + GetForwardVector() * TraceDistance;
	FCollisionQueryParams QueryParams;
	
	if(IgnoredActor)
	{
		QueryParams.AddIgnoredActor(IgnoredActor);      
	}
	
	bool Results = GetWorld()->LineTraceMultiByChannel(HitResults, StartLocation, End,
														ECC_WorldStatic, QueryParams);
	if(Results)
	{
		for (const FHitResult& Hit : HitResults)
		{
			DrawDebugLine(GetWorld(), StartLocation, Hit.ImpactPoint,
				FColor::Yellow, false, 1.f);

			IsWallInRange(WallHangRange, Hit);
		}
		return true;
	}
	
	DrawDebugLine(GetWorld(), StartLocation, End, FColor::Green, false, .2f);
	return false;
}

//---------------------------------

bool UWallDetectorComponent::IsWallInRange(const float& WallHangRange, const FHitResult& HitResult)
{
	if(!WallHangRange || !HitResult.GetComponent())
	{
		return false;
	}
	
	if(HitResult.GetComponent()->GetCollisionObjectType() == ECC_WorldStatic)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange,
								HitResult.Component->GetName());

		const float Distance = FVector::Dist(GetComponentLocation(), HitResult.ImpactPoint);
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange,
								FString::Printf(TEXT("Distance: %f"), Distance));

		return bIsWallInRange = Distance < WallHangRange;
	}
	return false;
}

