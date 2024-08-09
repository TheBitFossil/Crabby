// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformerGameInstance.h"

#include "ItemSpawner.h"


void UPlatformerGameInstance::Init()
{
	Super::Init();
}

//---------------------------------

void UPlatformerGameInstance::SetHealth(const float& Val)
{
	PlayerData.HitPoints = FMath::Clamp(Val, 0, PlayerData.MaxHitPoints);

	HealthChangedDelegate.Broadcast(PlayerData.HitPoints);
}

//---------------------------------

void UPlatformerGameInstance::RemoveHealthInstant(const float& ActualDamage)
{
	const float HitPointsLeft = PlayerData.HitPoints - ActualDamage;
	UE_LOG(LogTemp, Warning, TEXT("GI->Data(%f), Damage(%f), HitPointsLeft(%f)"), PlayerData.HitPoints, ActualDamage, HitPointsLeft);
	PlayerData.HitPoints = FMath::Clamp(HitPointsLeft, 0, PlayerData.MaxHitPoints);
		
	HealthChangedDelegate.Broadcast(PlayerData.HitPoints);
}

//---------------------------------

void UPlatformerGameInstance::SetHealthDelayed(const float& Val)
{
	PlayerData.HitPointsDelayed = FMath::Abs(Val);
	if(PlayerData.HitPointsDelayed > PlayerData.MaxHitPoints)
	{
		PlayerData.HitPointsDelayed = PlayerData.MaxHitPoints;
	}
	/* Callback inside Base Hud */
	HealthDelayChangedDelegate.Broadcast(PlayerData.HitPointsDelayed);
}

//---------------------------------

void UPlatformerGameInstance::KeepWithinBounds(const float& ReduceDelayedValue, const float& LowestValue, float& LastValue)
{
	if(ReduceDelayedValue < LowestValue)
	{
		// Stop reducing and update both values to be the same: "new last" or "max"
		LastValue = LowestValue;
	}
	else
	{
		// Keep reducing & allow Value change
		LastValue = ReduceDelayedValue;
	}
}

//---------------------------------

void UPlatformerGameInstance::HealthDelayed(const float& Val)
{
	//UE_LOG(LogTemp, Warning, TEXT("GI->Remove Delayed: Val(%f), Data(%f)"), Val, PlayerData.HitPointsDelayed);

	// Ensure the new delayed hit points are within bounds
	KeepWithinBounds(Val, PlayerData.HitPoints, PlayerData.HitPointsDelayed);
	
	//UE_LOG(LogTemp, Warning, TEXT("PlayerData.HitPointsDelayed left (%f)"), PlayerData.HitPointsDelayed);
	HealthDelayChangedDelegate.Broadcast(PlayerData.HitPointsDelayed);
}

//---------------------------------

void UPlatformerGameInstance::AddHealth(const float& Val)
{
	// Update Instant Health Variable
	const float NewHealth = PlayerData.HitPoints + Val;
	PlayerData.HitPoints = FMath::Clamp(NewHealth, 0, PlayerData.MaxHitPoints);
	
	// Update Instant ProgressBar
	HealthChangedDelegate.Broadcast(PlayerData.HitPoints);

	// Update Delayed ProgressBar & Broadcast
	SetHealthDelayed(PlayerData.HitPoints);
}

//---------------------------------

void UPlatformerGameInstance::RemoveStamina(const float& Val)
{
	const float StaminaLeft = PlayerData.Stamina - Val;
	PlayerData.Stamina = FMath::Clamp(StaminaLeft, 0, PlayerData.MaxStamina);

	StaminaChangedDelegate.Broadcast(PlayerData.Stamina);
}

//---------------------------------

void UPlatformerGameInstance::SetStaminaDelayed(const float& Val)
{
	PlayerData.StaminaDelayed = FMath::Abs(Val);
	if(PlayerData.StaminaDelayed > PlayerData.MaxStamina)
	{
		PlayerData.StaminaDelayed = PlayerData.MaxStamina;
	}
	/* Callback inside Base Hud */
	StaminaDelayChangedDelegate.Broadcast(PlayerData.StaminaDelayed);
}

//---------------------------------

void UPlatformerGameInstance::StaminaDelayed(const float& Val)
{
	KeepWithinBounds(Val, PlayerData.Stamina, PlayerData.StaminaDelayed);

	StaminaDelayChangedDelegate.Broadcast(PlayerData.StaminaDelayed);
}

//---------------------------------

void UPlatformerGameInstance::AddStamina(const float& Val)
{
	// Update instant Stamina 
	const float NewStamina = PlayerData.Stamina + Val;
	PlayerData.Stamina = FMath::Clamp(NewStamina, 0, PlayerData.MaxStamina);

	// Update instant Stamina Progress Bar
	StaminaChangedDelegate.Broadcast(PlayerData.Stamina);

	// Update delayed Stamina Progress Bar & Broadcast
	SetStaminaDelayed(PlayerData.Stamina);
}

//---------------------------------

void UPlatformerGameInstance::SetStamina(const float& Val)
{
	PlayerData.Stamina = FMath::Clamp(Val, 0, PlayerData.MaxStamina);
	
	StaminaChangedDelegate.Broadcast(PlayerData.Stamina);
}

//---------------------------------

void UPlatformerGameInstance::AddCredits(const float& Val)
{
	PlayerData.Credits += FMath::Abs(Val);
	
	CreditsChangedDelegate.Broadcast(PlayerData.Credits);
}

//---------------------------------

void UPlatformerGameInstance::UpdateDashBar(const float& CurrentDashTimer)
{
	DashBarChangedDelegate.Broadcast(CurrentDashTimer);
}

//---------------------------------

void UPlatformerGameInstance::ResetDashBar()
{
	DashBarChangedDelegate.Broadcast(0.f);
}

//---------------------------------

void UPlatformerGameInstance::OnItemCollected(const ALootItem* ItemCollected, const AActor* Collector)
{
	switch (ItemCollected->GetItemType())
	{
	case ECollectableType::Potion:
		AddHealth(ItemCollected->GetItemData().Health);
		break;
	case ECollectableType::Buff:
		AddStamina(ItemCollected->GetItemData().Stamina);
		UE_LOG(LogTemp, Warning, TEXT("ItemValue->%f, AttributeName->%d"), ItemCollected->GetItemData().Stamina, ItemCollected->GetItemType());
		break;
	case ECollectableType::Credits:
		AddCredits(ItemCollected->GetItemData().Credits);
		break;
	}
}

//---------------------------------

/* This is called by ItemSpawners on BeginPlay. Instead of calling FindAllObjectsOfClass */
void UPlatformerGameInstance::RegisterItemSpawner(AItemSpawner* ItemSpawner)
{
	if(!ItemSpawners.Contains(ItemSpawner))
	{
		ItemSpawners.AddUnique(ItemSpawner);
		ItemSpawner->ItemSpawnerCollectedItemDelegate.AddDynamic(this, &UPlatformerGameInstance::OnItemCollected);
		ItemSpawner->bAllowSpawn = true;
	}
}

//---------------------------------

void UPlatformerGameInstance::LevelChanged()
{
	LevelChangedDelegate.Broadcast(PlayerData.CurrentLevel);
}

