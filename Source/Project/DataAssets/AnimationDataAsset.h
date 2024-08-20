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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	int AnimationCount{0};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	int AnimationCost{0};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	int AnimationDamage{0};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	EAnimationDataType AnimationType{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	TArray<TSoftObjectPtr<UPaperZDAnimSequence>> AnimationSequences;
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECT_API UAnimationDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UAnimationDataAsset();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		FAnimationData Data;
	
	UFUNCTION(BlueprintCallable)
		EAnimationDataType GetAnimationType() const {return Data.AnimationType;}
};
