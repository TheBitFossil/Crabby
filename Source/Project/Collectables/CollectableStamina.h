// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LootItem.h"
#include "CollectableStamina.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ACollectableStamina : public ALootItem
{
	GENERATED_BODY()
	ACollectableStamina();
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
