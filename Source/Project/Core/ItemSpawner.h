// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

class UPlatformerGameInstance;
class ALootItem;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemSpawnerCollectedItem,const ALootItem*, ItemCollected, const AActor*, Collector);
UCLASS()
class PROJECT_API AItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemSpawner();

	FOnItemSpawnerCollectedItem ItemSpawnerCollectedItemDelegate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bAllowSpawn {false};

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<UPlatformerGameInstance> GameInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<ALootItem> ItemToSpawn;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SpawnItem();

	UFUNCTION()
	void OnItemCollected(const ALootItem* ItemCollected, const AActor* Collector);
};
