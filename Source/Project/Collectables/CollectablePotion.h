// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LootItem.h"
#include "CollectablePotion.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ACollectablePotion : public ALootItem
{
	GENERATED_BODY()

public:
	ACollectablePotion();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FCollectableItemData ItemData;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
