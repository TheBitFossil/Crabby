// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimNotifyState.h"
#include "AnimNotifyPlayerAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UAnimNotifyPlayerAttack : public UPaperZDAnimNotifyState
{
	GENERATED_BODY()

	virtual void TickNotify(float DeltaTime, float Playtime, float LastPlaybackTime, UPrimitiveComponent* AnimRenderComponent, bool& bPersistentActiveState, UPaperZDAnimInstance* OwningInstance) const override;
	virtual void OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
	virtual void OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
	virtual void OnNotifyAborted(UPaperZDAnimInstance* OwningInstance) const override;
};
