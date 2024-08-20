// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimNotify.h"
#include "AnimNotify_DashEnded.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UAnimNotify_DashEnded : public UPaperZDAnimNotify
{
	GENERATED_BODY()
public:
	UAnimNotify_DashEnded();
	
protected:
	virtual void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
	virtual void OnNotifyAborted(UPaperZDAnimInstance* OwningInstance) const override;
	virtual void TickNotify(float DeltaTime, float Playtime, float LastPlaybackTime, UPrimitiveComponent* AnimRenderComponent, bool& bPersistentActiveState, UPaperZDAnimInstance* OwningInstance) const override;
};
