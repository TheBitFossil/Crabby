// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Project/Player/PlayerCharacter2D.h"
#include "AnimationComboComponent.generated.h"

class UPaperZDAnimInstance;
class APlayerCharacter2D;
/**
 * Attack Combo Component
 * Handles detection of Hits: AttackCounter
 * Communicates with current Animation: Combo Window
 * Plays correct Animation on Input
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_API UAnimationComboComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAnimationComboComponent();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<APlayerCharacter2D> PlayerCharacter2D = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<UPaperZDAnimInstance> AnimInstance = nullptr;
	
	virtual void BeginPlay() override;
	void Melee(const FInputActionValue& InputActionValue);
	void Sword(const FInputActionValue& InputActionValue);
	void Bow(const FInputActionValue& InputActionValue);
	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ChangeAnimation(const EAnimationState& AnimationState);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int AttackCounter {};
};
