// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformerGameInstance.h"

#include "ItemSpawner.h"
#include "Project/Player/PlayerCharacter2D.h"


void UPlatformerGameInstance::Init()
{
	Super::Init();
}

//---------------------------------

void UPlatformerGameInstance::SetHealth(const int32& Val)
{
	PlayerData.HP = FMath::Clamp(Val, 0, PlayerData.MaxHP);

	HealthChangedDelegate.Broadcast(PlayerData.HP);
}

//---------------------------------

void UPlatformerGameInstance::RemoveHealth(const int32& ActualDamage)
{
	const int32 HitPointsLeft = PlayerData.HP - ActualDamage;
	PlayerData.HP = FMath::Clamp(HitPointsLeft, 0, PlayerData.MaxHP);

	HealthChangedDelegate.Broadcast(PlayerData.HP);
}

//---------------------------------

void UPlatformerGameInstance::RemoveHealthDelayed(const int32& Val)
{
	const int32 NewDelayedHealth = PlayerData.HPDelayed - Val;
	PlayerData.HPDelayed = FMath::Clamp(NewDelayedHealth, 0, PlayerData.HPDelayed);

	HealthDelayChangedDelegate.Broadcast(PlayerData.HPDelayed);
}

//---------------------------------

void UPlatformerGameInstance::AddHealth(const int32& Val)
{
	const float NewHealth = PlayerData.HP + Val;
	PlayerData.HP = FMath::Clamp(NewHealth, 0, PlayerData.MaxHP);

	HealthChangedDelegate.Broadcast(PlayerData.HP);
}

//---------------------------------

void UPlatformerGameInstance::RemoveStamina(const int32& Val)
{
	const float StaminaLeft = PlayerData.SP - Val;
	PlayerData.SP = FMath::Clamp(StaminaLeft, 0, PlayerData.MaxSP);

	StaminaChangedDelegate.Broadcast(PlayerData.SP);
}

//---------------------------------

void UPlatformerGameInstance::RemoveStaminaDelayed(const int32& Val)
{
	const float StaminaDelayedLeft = PlayerData.SPDelayed - Val;
	PlayerData.SPDelayed = FMath::Clamp(StaminaDelayedLeft, 0, PlayerData.MaxSP);
	
	StaminaDelayChangedDelegate.Broadcast(PlayerData.SPDelayed);
}

//---------------------------------

void UPlatformerGameInstance::AddStamina(const int32& Val)
{
	const float StaminaLeft = PlayerData.SP + Val;
	PlayerData.SP = FMath::Clamp(StaminaLeft, 0, PlayerData.MaxSP);

	StaminaChangedDelegate.Broadcast(PlayerData.SP);
}

//---------------------------------

void UPlatformerGameInstance::SetStamina(const int32& Val)
{
	PlayerData.SP = FMath::Clamp(Val, 0, PlayerData.MaxSP);
	
	StaminaChangedDelegate.Broadcast(PlayerData.SP);
}

//---------------------------------

void UPlatformerGameInstance::AddCredits(const int32& Val)
{
	PlayerData.Credits += Val;
	
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
		RemoveStamina(ItemCollected->GetItemData().Stamina);
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

