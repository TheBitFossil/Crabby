// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectablePotion.h"


ACollectablePotion::ACollectablePotion()
	: ALootItem()
{
	ItemData = FCollectableItemData{25.0f, 0.f, 0};

	ItemType = ECollectableType::Potion;
}

//---------------------------------

void ACollectablePotion::BeginPlay()
{
	Super::BeginPlay();
}

//---------------------------------

void ACollectablePotion::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

//---------------------------------

void ACollectablePotion::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ...
}
