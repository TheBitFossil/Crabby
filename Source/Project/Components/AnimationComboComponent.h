// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Project/Player/PlayerCharacter2D.h"
#include "AnimationComboComponent.generated.h"

class UPaperZDAnimInstance;
class APlayerCharacter2D;
class UAnimationDataAsset;

UENUM(BlueprintType)
enum EAnimationState
{
	Walking,
	Dashing,
	Running,
	Punching,
	Kick,
	Block,
	Grab,
	Sword,
	Bow,
	Aim,
	Crouched,
	GettingHit,
	Rolling
};

UENUM(BlueprintType)
enum class EComboState : uint8
{
	ComboStart,
	ComboEnd
};

UENUM(BlueprintType)
enum class EComboType : uint8
{
	Punch	UMETA(DisplayName ="Punch"),
	Kick	UMETA(DisplayName ="Kick"),
	Sword	UMETA(DisplayName ="Sword"),
};


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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation")
		TObjectPtr<UPaperZDAnimInstance> AnimInstance = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation")
		TEnumAsByte<EAnimationState> AnimationState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UPaperZDAnimSequence* LastSequenceCompleted;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Combo")
		int32 AttackCounter {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Combo")
		bool bHasHit{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Combo")
		bool bCanComboFromCurrentSequence{};
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Animation|Combo")
		float HitComboWindowTime{2.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Combo")
		float ComboCooldownTime{3.0f};
	
	FTimerHandle HitComboTimerHandle;
	FTimerHandle ComboCooldownTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Animation|Datas")
		EComboState ComboState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Animation|Datas")
		EComboType LastComboType;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Animation|Datas")
		TMap<EComboType, TObjectPtr<UAnimationDataAsset>> ComboDataAssets;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSequenceComplete(const UPaperZDAnimSequence* AnimSequence);

	UFUNCTION()
	void OnSequenceChanged(const UPaperZDAnimSequence* From, const UPaperZDAnimSequence* To, float CurrentProgress);

	void PlayNextComboSequence(const int32 Counter);
	
public:
	TEnumAsByte<EAnimationState>& GetAnimationState() {return AnimationState;}
	void SetAnimationState(const EAnimationState& NextState);

	UFUNCTION(BlueprintCallable)
	void StartComboSequence();

	UFUNCTION(BlueprintCallable)
	bool TryComboAttack();

	UFUNCTION()
	void SetHasHit(const bool Success) {bHasHit = Success;}

	UFUNCTION(BlueprintCallable)
	void StartComboWindowTimer();

	UFUNCTION(BlueprintCallable)
	void StopComboWindowTimer();

	UFUNCTION()
	void OnHitComboTimerTimeOut();

	UFUNCTION()
	void OnCooldownTimerTimeOut();
	
	void OnAnimNotifyComboHasEnded(bool bIsActive, const UPaperZDAnimSequence* PaperZdAnimSequence);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool CanAttack();
};
