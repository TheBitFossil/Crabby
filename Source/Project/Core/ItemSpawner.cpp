// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"

#include "PlatformerGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Project/Collectables/LootItem.h"

AItemSpawner::AItemSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

}

//---------------------------------

void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<UPlatformerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(GameInstance)
	{
		GameInstance->RegisterItemSpawner(this);
	}
	
	if(bAllowSpawn && ItemToSpawn)
	{
		SpawnItem();
	}
}

//---------------------------------

void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//---------------------------------

void AItemSpawner::SpawnItem()
{
	FVector SpawnLocation = GetActorLocation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	if(ItemToSpawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemToSpawn is not set."));
		return;
	}
	if (!ItemToSpawn->IsChildOf(ALootItem::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemToSpawn is not a valid subclass of ALootItem."));
		return;
	}
	
	if(UWorld* World = GetWorld())
	{
		ALootItem* SpawnedItem = World->SpawnActor<ALootItem>(
			ItemToSpawn,
			SpawnLocation,
			FRotator::ZeroRotator,
			SpawnParams
		);
		if(SpawnedItem)
		{
			SpawnedItem->ItemCollectedDelegate.AddDynamic(this, &AItemSpawner::OnItemCollected);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to spawn item."));
		}
	}
}

//---------------------------------

/* Callback should be part of the GameInstance */
void AItemSpawner::OnItemCollected(const ALootItem* ItemCollected, const AActor* Collector)
{
	if(!ItemCollected || !Collector)
	{
		return;
	}

	/* Callback inside GameInstance */
	ItemSpawnerCollectedItemDelegate.Broadcast(ItemCollected, Collector);
}

