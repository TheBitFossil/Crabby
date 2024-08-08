// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LootItem.h"
#include "GameFramework/Actor.h"
#include "CollectableCredits.generated.h"

UCLASS()
class PROJECT_API ACollectableCredits : public ALootItem
{
	GENERATED_BODY()

public:
	ACollectableCredits();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
