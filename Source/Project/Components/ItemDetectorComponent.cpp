// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDetectorComponent.h"

#include "Project/Interfaces/ICollectable.h"
#include "Project/Player/PlayerCharacter2D.h"


// Sets default values for this component's properties
UItemDetectorComponent::UItemDetectorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

//---------------------------------

// Called when the game starts
void UItemDetectorComponent::BeginPlay()
{
	Super::BeginPlay();

	if(APlayerCharacter2D* Owner = Cast<APlayerCharacter2D>(GetOwner()))
	{
		Owner->OnActorBeginOverlap.AddDynamic(this, &UItemDetectorComponent::OnOverlapBegin);
	}
}

//---------------------------------

void UItemDetectorComponent::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald,
			FString::Printf(TEXT("Overlap from Player to Other: %s"), *OtherActor->GetName()));

	if (OtherActor && OtherActor->GetClass()->ImplementsInterface(UICollectable::StaticClass()))
	{
		IICollectable::Execute_ICollect(OtherActor, GetOwner());
	
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald,
			FString::Printf(TEXT("Overlap with Interface: %s"), *OtherActor->GetName()));
	}
}

// Called every frame
void UItemDetectorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

