// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICollectable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UICollectable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_API IICollectable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Interacing)
	void ICollect(const AActor* Collector);
};
