// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlatformerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UPlatformerGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float PlayerHP{350.f};

	void SetPlayerHP(float NewHP);
	
};
