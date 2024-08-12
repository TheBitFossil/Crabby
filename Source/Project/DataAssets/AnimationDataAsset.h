// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AnimationDataAsset.generated.h"

/**
 * 
 */
class UPaperZDAnimSequence;

UENUM(BlueprintType)
enum class EAnimationDataType : uint8
{
	Punch,
	Kick,
	Sword
};

USTRUCT(BlueprintType)
struct FAnimationData
{
	GENERATED_BODY()

	int AnimationCount{0};

	int AnimationCost{0};

	int AnimationDamage{0};

	EAnimationDataType AnimationType;

	TArray<TSoftObjectPtr<UPaperZDAnimSequence>> AnimationSequences;
};

/**
 * 
 */
UCLASS()
class PROJECT_API UAnimationDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UAnimationDataAsset();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		FAnimationData Data;
	
	UFUNCTION(BlueprintCallable)
	int GetAnimationCount() const {return Data.AnimationSequences.Num();}
	
	UFUNCTION(BlueprintCallable)
	EAnimationDataType GetAnimationType() const {return Data.AnimationType;}
};
