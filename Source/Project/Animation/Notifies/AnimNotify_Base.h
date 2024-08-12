// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimNotify.h"
#include "AnimNotify_Base.generated.h"

class APlayerCharacter2D;
class UAnimationComboComponent;
/**
 * 
 */
UCLASS()
class PROJECT_API UAnimNotify_Base : public UPaperZDAnimNotify
{
	GENERATED_BODY()
public:
	UAnimNotify_Base();

	
protected:
	// Store the reference to the PlayerCharacter2D (mutable to allow modification in const methods)
	mutable TObjectPtr<APlayerCharacter2D> Player2D;
	
	// Store the reference to the Animation Combo Component (mutable to allow modification in const methods)
	mutable TObjectPtr<UAnimationComboComponent> ComboComponent;

	void InitComponents(APlayerCharacter2D* OwningActor) const;
	
	virtual void TickNotify(float DeltaTime, float Playtime, float LastPlaybackTime, UPrimitiveComponent* AnimRenderComponent, bool& bPersistentActiveState, UPaperZDAnimInstance* OwningInstance) const override;

	virtual void OnNotifyAborted(UPaperZDAnimInstance* OwningInstance) const override;

	virtual void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
};
