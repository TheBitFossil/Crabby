// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableStamina.h"

ACollectableStamina::ACollectableStamina()
	: ItemData(FCollectableItemData{0.f, 25.f, 0})
{
	
}

//---------------------------------

void ACollectableStamina::BeginPlay()
{
	Super::BeginPlay();
}

//---------------------------------

void ACollectableStamina::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

//---------------------------------

void ACollectableStamina::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	
}
