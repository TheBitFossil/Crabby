// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Project/Collectables/LootItem.h"
#include "PlatformerGameInstance.generated.h"

class AItemSpawner;
struct FCollectableItemData;
enum class ECollectableType : uint8;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, const float&, HP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthDelayChanged, const float&, HPDelayed);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, const float&, Stamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaDelayChanged, const float&, StaminaDelayed);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDashBarChanged, const float&, TimeLeft);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreditsChanged, const float&, Credits);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelChanged, const float&, CurrentLevel);

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MaxHitPoints{350.f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float HitPointsDelayed{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float HitPoints{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Credits{0.f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 Score{0};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MaxStamina{180.f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float StaminaDelayed{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Stamina{};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float DamageTaken{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float LastHealth{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float LastStamina{};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float MaxDashCoolDown{3.f};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float DashCoolDown{1.f};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float CurrentLevel{1.f};

	FPlayerData()
	{
		HitPoints = MaxHitPoints;
		LastHealth = HitPoints;
		HitPointsDelayed = HitPoints;
	
		Stamina = MaxStamina;
		LastStamina = Stamina;
		StaminaDelayed = Stamina;

		DamageTaken = 0.f;
		Score = 0.f;
	}
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FPlayerData PlayerData;
	
public:
	FOnHealthChanged HealthChangedDelegate;
	FOnHealthDelayChanged HealthDelayChangedDelegate;

	FOnStaminaChanged StaminaChangedDelegate;
	FOnStaminaDelayChanged StaminaDelayChangedDelegate;

	FOnDashBarChanged DashBarChangedDelegate;
	FOnCreditsChanged CreditsChangedDelegate;
	FOnLevelChanged LevelChangedDelegate;

	float GetHealth() const {return PlayerData.HitPoints;}
	float GetMaxHealth() const {return PlayerData.MaxHitPoints;}
	void SetHealth(const float& Val);
	void RemoveHealthInstant(const float& ActualDamage);
	void AddHealth(const float& Val);
	
	float GetHealthDelayed() const {return PlayerData.HitPointsDelayed;}
	void SetHealthDelayed(const float& Val);
	void HealthDelayed(const float& Val);

	float GetStamina() const {return PlayerData.Stamina;}
	float GetMaxStamina() const {return PlayerData.MaxStamina;}
	void SetStamina(const float& Val);
	void RemoveStamina(const float& Val);
	void AddStamina(const float& Val);
	
	float GetStaminaDelayed() const {return PlayerData.StaminaDelayed;}
	void SetStaminaDelayed(const float& Val);
	void StaminaDelayed(const float& Val);

	/* Is a ref for delayed HealthBar, no delegates */
	float& GetLastHealthRef() {return PlayerData.LastHealth;}
	
	/* Is a ref for delayed StaminaBar, no delegates */
	float& GetLastStaminaRef() {return PlayerData.LastStamina;}

	/* Is a cached value for the delayed HealthBar, no delegates */
	float GetDamageTaken() const {return PlayerData.DamageTaken;}
	void SetDamageTaken(const float& Val)
	{
		PlayerData.DamageTaken = Val;
	}
	
	float GetCredits() const {return PlayerData.Credits;}
	void AddCredits(const float& Val);

	/* Is a cached value for the delayed HealthBar, no delegates */
	float GetDashCoolDown() const {return PlayerData.DashCoolDown;}
	float GetMaxDashCoolDown() const {return PlayerData.MaxDashCoolDown;}
	void SetDashCoolDown(const float& Val)
	{
		PlayerData.DashCoolDown = Val;
	}

	float GetCurrentLevel() const{return PlayerData.CurrentLevel;}
	
	void UpdateDashBar(const float& CurrentDashTimer);
	void ResetDashBar();

	void KeepWithinBounds(const float& ReduceDelayedValue, const float& LowestValue, float& LastValue);
	
	UFUNCTION()
	void OnItemCollected(const ALootItem* ItemCollected, const AActor* Collector);
	
	void RegisterItemSpawner(AItemSpawner* ItemSpawner);

	void LevelChanged();
};
