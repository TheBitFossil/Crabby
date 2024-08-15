// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotify_Base.h"
#include "AnimNotify_StopMovement.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UAnimNotify_StopMovement : public UAnimNotify_Base
{
	GENERATED_BODY()
	UAnimNotify_StopMovement();
		
protected:
	virtual void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
	virtual void OnNotifyAborted(UPaperZDAnimInstance* OwningInstance) const override;
	virtual void TickNotify(float DeltaTime, float Playtime, float LastPlaybackTime, UPrimitiveComponent* AnimRenderComponent, bool& bPersistentActiveState, UPaperZDAnimInstance* OwningInstance) const override;
	
};
