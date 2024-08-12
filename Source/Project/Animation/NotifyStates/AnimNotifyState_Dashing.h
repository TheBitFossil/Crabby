// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifyStateBase.h"
#include "AnimNotifyState_Dashing.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UAnimNotifyState_Dashing : public UAnimNotifyStateBase
{
	GENERATED_BODY()
	UAnimNotifyState_Dashing();

protected:
	virtual void TickNotify(float DeltaTime, float Playtime, float LastPlaybackTime, UPrimitiveComponent* AnimRenderComponent, bool& bPersistentActiveState, UPaperZDAnimInstance* OwningInstance) const override;

	virtual void OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
};
