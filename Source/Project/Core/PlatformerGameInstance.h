// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Project/Collectables/LootItem.h"
#include "PlatformerGameInstance.generated.h"

class AItemSpawner;
struct FCollectableItemData;
enum class ECollectableType : uint8;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, const int32&, HP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthDelayChanged, const int32&, HPDelayed);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, const int32&, Stamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaDelayChanged, const int32&, StaminaDelayed);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDashBarChanged, const float&, TimeLeft);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreditsChanged, const int32&, Credits);

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 MaxHP{350};

	/* Set this to MaxHP, Value is the last highest HP value.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 HPDelayed{350};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 HP{200};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 Credits{0};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 MaxSP{180};

	/* Set this to MaxSP, Value is the last highest SP value.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 SPDelayed{180};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 SP{80};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float MaxDashCoolDown{3.f};
	
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<TObjectPtr<AItemSpawner>> ItemSpawners;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FPlayerData PlayerData;

	FOnHealthChanged HealthChangedDelegate;
	FOnHealthDelayChanged HealthDelayChangedDelegate;

	FOnStaminaChanged StaminaChangedDelegate;
	FOnStaminaDelayChanged StaminaDelayChangedDelegate;

	FOnDashBarChanged DashBarChangedDelegate;
	
	FOnCreditsChanged CreditsChangedDelegate;
	
	void SetHealth(const int32& Val);
	
	void RemoveHealth(const int32& ActualDamage);

	void RemoveHealthDelayed(const int32& Val);

	void AddHealth(const int32& Health);
	
	void SetStamina(const int32& Val);
	
	void RemoveStamina(const int32& Val);

	void RemoveStaminaDelayed(const int32& Val);
	
	void AddStamina(const int32& Val);

	void AddCredits(const int32& Val);

	void UpdateDashBar(const float& CurrentDashTimer);
	
	void ResetDashBar();

	UFUNCTION()
	void OnItemCollected(const ALootItem* ItemCollected, const AActor* Collector);
	
	void RegisterItemSpawner(AItemSpawner* ItemSpawner);
	

};
