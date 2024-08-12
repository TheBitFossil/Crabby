// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimNotifyState.h"
#include "AnimNotifyStateBase.generated.h"

class UAnimationComboComponent;
class APlayerCharacter2D;

/**
 *  Base Class for all AnimNotifies
 *  
 *  In case we want all States to have something in common
 *  The project is heavy in animations and notifies
 */
UCLASS(Abstract)
class PROJECT_API UAnimNotifyStateBase : public UPaperZDAnimNotifyState
{
	GENERATED_BODY()
public:
	UAnimNotifyStateBase();
	
protected:
	// Store the reference to the PlayerCharacter2D (mutable to allow modification in const methods)
	mutable TObjectPtr<APlayerCharacter2D> Player2D;
	
	// Store the reference to the Animation Combo Component (mutable to allow modification in const methods)
	mutable TObjectPtr<UAnimationComboComponent> ComboComponent;
	
	virtual void TickNotify(float DeltaTime, float Playtime, float LastPlaybackTime, UPrimitiveComponent* AnimRenderComponent, bool& bPersistentActiveState, UPaperZDAnimInstance* OwningInstance) const override;

	void InitComponents(APlayerCharacter2D* Player) const;

	virtual void OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const override;

	virtual void OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const override;

	virtual void OnNotifyAborted(UPaperZDAnimInstance* OwningInstance) const override;
};
