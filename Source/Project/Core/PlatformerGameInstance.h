// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Project/Collectables/LootItem.h"
#include "PlatformerGameInstance.generated.h"

class AItemSpawner;
struct FCollectableItemData;
enum class ECollectableType : uint8;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, HP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, float, Stamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreditsChanged, int32, Credits);

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHP{350.f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float HP{200.f};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Credits{0};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxStamina{200.f};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Stamina{200.f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DashCoolDown{3.f};
};

/**
 * 
 */
UCLASS()
class PROJECT_API UPlatformerGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void Init() override;

protected:
	float MaxHealth{400.f};
	float MaxStamina{200.f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<TObjectPtr<AItemSpawner>> ItemSpawners;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FPlayerData PlayerData;

	void SetHP(float Val);
	
	void AddCredits(int32 Val);
	
	void RemoveStamina(float Val);

	void AddStamina(float Val);
	
	void SetStamina(int I);
	
	void RemoveHealth(float ActualDamage);
	
	void AddHealth(float Health);

	UFUNCTION()
	void OnItemCollected(const ALootItem* ItemCollected, const AActor* Collector);
	
	void RegisterItemSpawner(AItemSpawner* ItemSpawner);
};
