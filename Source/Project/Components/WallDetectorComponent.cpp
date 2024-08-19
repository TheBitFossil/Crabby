// Fill out your copyright notice in the Description page of Project Settings.


#include "WallDetectorComponent.h"


UWallDetectorComponent::UWallDetectorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

//---------------------------------

void UWallDetectorComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

//---------------------------------

void UWallDetectorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!bIsProcessing || !GetOwner())
	{
		return;
	}

	DetectWall();
}

//---------------------------------

void UWallDetectorComponent::DetectWall()
{
	DetectedWallDistance = MAX_FLT;
	
	const FVector OffsetForward = GetOwner()->GetActorForwardVector() * OffsetDistance;
	const FVector StartLocation = GetOwner()->GetActorLocation() + OffsetForward;
	const FVector End = StartLocation + GetOwner()->GetActorForwardVector() * TraceDistance;
	DrawDebugLine(GetWorld(), StartLocation, End, FColor::Green, false, .2f);
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());      
	
	bool bHit = GetWorld()->LineTraceMultiByChannel(HitResults, StartLocation, End, ECC_WorldStatic, QueryParams);
	if(bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			DrawDebugLine(GetWorld(), StartLocation, Hit.ImpactPoint,
				FColor::Red, false, 1.f);

			if(Hit.GetComponent()->GetCollisionObjectType() == ECC_WorldStatic)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Orange, Hit.Component->GetName());
				WallActor = Hit.GetActor();
				
				const float Distance = FVector::Dist(GetOwner()->GetActorLocation(), Hit.ImpactPoint);
				GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Orange,FString::Printf(TEXT("Distance: %f"), Distance));

				DetectedWallDistance = Distance;
				
				bHasDetectedActor = true;
				return;	// Exit the function early if a wall is detected.
			}
		}
	}

	// If no wall was detected, clear the WallActor and set the flag to false
	WallActor = nullptr;
	bHasDetectedActor = false;
}
