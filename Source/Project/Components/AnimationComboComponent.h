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
	Melee,
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
	None,
	Combo,
	ComboEnd
};

UENUM(BlueprintType)
enum class EComboType : uint8
{
	None	UMETA(DisplayName = "None"),
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
		TEnumAsByte<EAnimationState> AnimationState{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Debug")
		const UPaperZDAnimSequence* LastSequenceCompleted{};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Combo")
		int32 HitCounter {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Combo")
		bool bHasHit{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Combo")
		bool bCanComboFromCurrentSequence{};

	/* Time in Seconds to Input new Attack*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Animation|Combo")
		float HitComboWindowTime{2.0f};

	/* Time in Seconds to Player can not Attack after finishing Last Combo Attack*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Combo")
		float ComboCooldownTime{3.0f};
	
	FTimerHandle HitComboTimerHandle;
	FTimerHandle ComboCooldownTimerHandle;

	/* We can either continue our Combo or we are done */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Animation|Datas")
		EComboState ComboState{};

	/* Cache which was our Last Type of Combo. You might want to make adjustments Punch->Kick etc. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Animation|Datas")
		EComboType ComboInputType{};

	/* This is where you store your Assets Data. Right now Data Assets for each type of Combo with Arrays of Animations. */
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Animation|Datas")
		TMap<EComboType, TObjectPtr<UAnimationDataAsset>> ComboDataAssets{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Debug")
		UPaperZDAnimSequence* ComboAttackOverrideAnimationSequence{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Debug")
		EAnimationDataType ComboAnimationDataType{};
	
	FZDOnAnimationOverrideEndSignature OnComboAttackOverrideDelegate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Debug")
		int MaxComboCount{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation|Debug")
		bool bOverrideCompleted {};

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSequenceComplete(const UPaperZDAnimSequence* AnimSequence);

	UFUNCTION()
	void OnSequenceChanged(const UPaperZDAnimSequence* From, const UPaperZDAnimSequence* To, float CurrentProgress);

	UFUNCTION()
	void OnComboAttackOverride(bool Completed);

public:
	TEnumAsByte<EAnimationState>& GetAnimationState() {return AnimationState;}
	void SetAnimationState(const EAnimationState& NextState);

	UFUNCTION(BlueprintCallable)
	void AttackCombo(const EAnimationState& AttackInput);

	/* Called only from the Player when he has Hit a target. */
	void StartTimer(FTimerHandle& TimerHandle, void (UAnimationComboComponent::*TimerCallBack)(), float TimerDuration);

	void StopTimer(FTimerHandle& TimerHandle);

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
};
