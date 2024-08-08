// Fill out your copyright notice in the Description page of Project Settings.


#include "LootItem.h"

#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"


ALootItem::ALootItem()
	: ItemData(FCollectableItemData{0.f, 0.f, 0})
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	SetRootComponent(CapsuleComponent);

	FlipBookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flip Book"));
	FlipBookComponent->SetupAttachment(RootComponent);
	
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ALootItem::OnOverlapBegin);
}

//---------------------------------

void ALootItem::ICollect_Implementation(const AActor* Collector)
{
	IICollectable::ICollect_Implementation(Collector);

	/* Callback inside ItemSpawner (owner) */
	ItemCollectedDelegate.Broadcast(this, Collector);

	Destroy();
}

//---------------------------------

void ALootItem::BeginPlay()
{
	Super::BeginPlay();

}

//---------------------------------

void ALootItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}
