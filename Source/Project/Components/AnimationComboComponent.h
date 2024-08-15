// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AnimSequences/Players/PaperZDAnimationPlaybackData.h"
#include "Project/Player/PlayerCharacter2D.h"
#include "AnimationComboComponent.generated.h"


UENUM(BlueprintType)
enum class ECurrentAnimStates : uint8
{
	Walking 		UMETA(DisplayName="Walking"),
	Dashing 		UMETA(DisplayName="Dashing"),
	Running 		UMETA(DisplayName="Running"),
	Attacking		UMETA(DisplayName="Attacking"),
	Blocking		UMETA(DisplayName="Blocking"),
	Grabbing 		UMETA(DisplayName="Grabbing"),
	Shooting		UMETA(DisplayName="Shooting"),
	Crouched 		UMETA(DisplayName="Crouched"),
	GettingHit 		UMETA(DisplayName="GettingHit"),
	Rolling 		UMETA(DisplayName="Rolling")
};

UENUM(BlueprintType)
enum class EComboType : uint8
{
	None	UMETA(DisplayName ="None"),
	Punch	UMETA(DisplayName ="Punch"),
	Kick	UMETA(DisplayName ="Kick"),
	Sword	UMETA(DisplayName ="Sword"),
};

/**
 * Attack Combo Component
 * Handles detection of Hits: AttackCounter
 * Communicates with Animation Blueprint via Notifies and Animation State changes
 * Should Play correct Animation on Input and blocks further Action if cant transition to next Combo
 */

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_API UAnimationComboComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAnimationComboComponent();

protected:
	/* The Character Class which uses this Combo Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<APlayerCharacter2D> PlayerCharacter2D = nullptr;

	/* This should reference your Animation Player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation")
		TObjectPtr<UPaperZDAnimInstance> AnimInstance = nullptr;

	/* Changing this State here, will change the ABP */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation")
		ECurrentAnimStates AnimationState = ECurrentAnimStates::Walking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Debug")
		const UPaperZDAnimSequence* LastSequenceCompleted{};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Combo")
		int32 HitCounter{0};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Combo")
		bool bHasHit{false};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Combo")
		bool bHasLastComboSequenceCompleted{true};

	/* Time in Seconds to Input new Attack*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Animation|Combo")
		float HitComboWindowTime{2.0f};

	/* Time in Seconds to Player can not Attack after finishing Last Combo Attack*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Combo")
		float ComboCooldownTime{3.0f};
	
	FTimerHandle HitComboTimerHandle;
	FTimerHandle ComboCooldownTimerHandle;

	/* Cache which was our Last Type of Combo. You might want to make adjustments Punch->Kick etc. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Animation|Datas")
		EComboType LastComboInputType{};

	/* This is where you store your Assets Data. Right now Data Assets for each type of Combo with Arrays of Animations. */
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Animation|Datas")
		TMap<EComboType, TObjectPtr<UAnimationDataAsset>> ComboDataAssets{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Debug")
		UPaperZDAnimSequence* ComboDataAnimSequence{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Debug")
		EAnimationDataType ComboAnimationDataType{};

	FZDOnAnimationOverrideEndSignature OnComboAttackOverrideDelegate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Debug")
		int MaxComboCount{2};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Debug")
		bool bOverrideCompleted {true};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Debug")
		TObjectPtr<UAnimationDataAsset> ComboDataAssetKey;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Debug")
		float AttackDamageCurrentHit{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Debug")
		float AttackCostCurrentHit{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Debug")
		float Time{};

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSequenceComplete(const UPaperZDAnimSequence* AnimSequence);
	void ResetComboSequence(const UPaperZDAnimSequence* FromAnimSequence, const UPaperZDAnimSequence* ToAnimSequence=nullptr);

	UFUNCTION()
	void OnSequenceChanged(const UPaperZDAnimSequence* From, const UPaperZDAnimSequence* To, float CurrentProgress);

	UFUNCTION()
	void OnComboAttackOverride(bool Completed);

	void CalculateAttackDamage(const float InDamage);
	void CalculateAttackCost(const float InCost);

public:
	ECurrentAnimStates GetAnimationState() const {return AnimationState;}
	void SetAnimationState(const ECurrentAnimStates NextState);

	UFUNCTION(BlueprintCallable)
	void RequestAttackCombo(const EComboType& InputAttackType);
	void StartAttackCombo(const EComboType& InputAttackType);

	/* Called only from the Player when he has Hit a target. */
	void StartTimer(FTimerHandle& TimerHandle, void (UAnimationComboComponent::*TimerCallBack)(), float TimerDuration);

	/* Called only from the ABP via AnimNotify */
	UFUNCTION(BlueprintCallable)
	void SetHasHit(const bool Success);

	UFUNCTION(BlueprintCallable)
	bool GetHasHit() const {return bHasHit;}
	
	UFUNCTION()
	void OnHitComboTimerTimeOut();

	UFUNCTION()
	void OnCooldownTimerTimeOut();

	/* To end a Combo, add Animation Notify to your last Animation from the DataAsset Array. */
	void OnAnimNotifyComboHasEnded(bool bIsActive, const UPaperZDAnimSequence* PaperZdAnimSequence);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* Internal check if we can Attack. Can block further Player Input */
	UFUNCTION(BlueprintCallable)
	bool CanAttack();

	UFUNCTION(BlueprintCallable)
	float GetAttackDamage();
};
