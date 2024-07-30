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
}

//---------------------------------

bool UWallDetectorComponent::IsDetectingWall(const AActor* IgnoredActor)
{
	DetectedWallDistance = MAX_FLT;
	
	const FVector StartLocation = GetComponentLocation();
	const FVector End = StartLocation + GetForwardVector() * TraceDistance;
	FCollisionQueryParams QueryParams;
	
	if(IgnoredActor)
	{
		QueryParams.AddIgnoredActor(IgnoredActor);      
	}
	
	bool bHit = GetWorld()->LineTraceMultiByChannel(HitResults, StartLocation, End,
														ECC_WorldStatic, QueryParams);
	if(bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			DrawDebugLine(GetWorld(), StartLocation, Hit.ImpactPoint,
				FColor::Red, false, 1.f);

			if(Hit.GetComponent()->GetCollisionObjectType() == ECC_WorldStatic)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Orange,
				//						Hit.Component->GetName());

				const float Distance = FVector::Dist(GetComponentLocation(), Hit.ImpactPoint);
				GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Orange,
										FString::Printf(TEXT("Distance: %f"), Distance));

				DetectedWallDistance = Distance;
				return true;
			}
		}
	}

	DrawDebugLine(GetWorld(), StartLocation, End, FColor::Green, false, .2f);
	return false;
}
