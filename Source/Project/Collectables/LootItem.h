// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Project/Interfaces/ICollectable.h"
#include "LootItem.generated.h"

class UPlatformerGameInstance;
class UPaperFlipbookComponent;
class UCapsuleComponent;

UENUM(BlueprintType)
enum class ECollectableType : uint8
{
	Potion,
	Credits,
	Buff,
};

USTRUCT(BlueprintType)
struct FCollectableItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Health{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Stamina{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Credits{};

	// Default C-Tor
	FCollectableItemData()
		: Health(0.f), Stamina(0.f), Credits(0.f)
	{
	}

	// C-Tor called from Child Items
	FCollectableItemData(float InHealth, float InStamina, int InCredits)
		: Health(InHealth), Stamina(InStamina), Credits(InCredits)
	{
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FItemCollectedDelegate, const ALootItem*, ItemCollected, const AActor*, Collector);
UCLASS(Abstract)
class PROJECT_API ALootItem : public AActor, public IICollectable
{
	GENERATED_BODY()
	
public:
	ALootItem();

	FItemCollectedDelegate ItemCollectedDelegate;

	FCollectableItemData GetItemData() const { return ItemData; }

	ECollectableType GetItemType() const { return ItemType; }
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TObjectPtr<UPaperFlipbookComponent> FlipBookComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Loot")
		ECollectableType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Loot")
		FCollectableItemData ItemData;
	
	virtual void ICollect_Implementation(const AActor* Collector) override;

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
