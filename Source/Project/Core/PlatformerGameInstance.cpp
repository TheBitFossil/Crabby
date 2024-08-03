// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformerGameInstance.h"

#include "ItemSpawner.h"
#include "Project/Player/PlayerCharacter2D.h"


void UPlatformerGameInstance::Init()
{
	Super::Init();
}

//---------------------------------

void UPlatformerGameInstance::SetHP(float Val)
{
	PlayerData.HP = Val;
	FMath::Clamp(PlayerData.HP, 0, PlayerData.MaxHP);
}

//---------------------------------

void UPlatformerGameInstance::AddCredits(int32 Val)
{
	PlayerData.Credits += Val;
}

//---------------------------------

void UPlatformerGameInstance::RemoveStamina(float Val)
{
	const float StaminaLeft = PlayerData.Stamina - Val;
	PlayerData.Stamina = StaminaLeft;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Stamina removed: %f"), PlayerData.Stamina));
}

//---------------------------------

void UPlatformerGameInstance::AddStamina(float Val)
{
	const float StaminaLeft = PlayerData.Stamina + Val;
	if(StaminaLeft > PlayerData.MaxStamina)
	{
		PlayerData.Stamina = PlayerData.MaxStamina;
	}
	else
	{
		PlayerData.Stamina = StaminaLeft;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Stamina added: %f"),PlayerData.Stamina));
}

//---------------------------------

void UPlatformerGameInstance::SetStamina(int Val)
{
	PlayerData.Stamina = Val;
	FMath::Clamp(PlayerData.Stamina, 0, PlayerData.MaxStamina);
}

//---------------------------------

void UPlatformerGameInstance::RemoveHealth(float ActualDamage)
{
	const float HitPointsLeft = PlayerData.HP - ActualDamage;
	PlayerData.HP = HitPointsLeft;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Health removed: %f"), PlayerData.HP));
}

//---------------------------------

void UPlatformerGameInstance::AddHealth(float Health)
{
	const float HitPointsLeft = PlayerData.HP + Health;
	if(HitPointsLeft > PlayerData.MaxHP)
	{
		PlayerData.HP = PlayerData.MaxHP;
	}
	else
	{
		PlayerData.HP = HitPointsLeft;
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		FString::Printf(TEXT("Health now at: %f"), PlayerData.HP));
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

	// Update HUD Class
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
