
#include "CollectableCredits.h"


ACollectableCredits::ACollectableCredits()
	: ItemData(FCollectableItemData{0.f, 0.f, 1})
{
	PrimaryActorTick.bCanEverTick = true;
}

//---------------------------------

void ACollectableCredits::BeginPlay()
{
	Super::BeginPlay();
}

//---------------------------------

void ACollectableCredits::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//---------------------------------

void ACollectableCredits::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ...
}

