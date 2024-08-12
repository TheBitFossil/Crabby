// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationComboComponent.h"
#include "PaperZDAnimInstance.h"
#include "AnimSequences/Players/PaperZDAnimPlayer.h"
#include "Project/DataAssets/AnimationDataAsset.h"
#include "Project/Player/PlayerCharacter2D.h"


UAnimationComboComponent::UAnimationComboComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

//---------------------------------

void UAnimationComboComponent::BeginPlay()
{
	Super::BeginPlay();

	if((PlayerCharacter2D = Cast<APlayerCharacter2D>(GetOwner())))
	{
		if((AnimInstance = Cast<UPaperZDAnimInstance>(PlayerCharacter2D->GetAnimInstance())))
		{
			// ...
			AnimInstance->GetPlayer()->OnPlaybackSequenceComplete.AddDynamic(this, &UAnimationComboComponent::OnSequenceComplete);
			AnimInstance->GetPlayer()->OnPlaybackSequenceChanged.AddDynamic(this, &UAnimationComboComponent::OnSequenceChanged);
		}
	}

	OnComboAttackOverrideDelegate.BindUObject(this, &UAnimationComboComponent::OnComboAttackOverride);
}



//---------------------------------

void UAnimationComboComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//---------------------------------

bool UAnimationComboComponent::CanAttack()
{
	// Is any Current State hindering our Ability ?
	if(GetAnimationState() == Dashing || ComboState == EComboState::ComboEnd || bOverrideCompleted )
	{
		UE_LOG(LogTemp, Error, TEXT("CanAttack(false), this case is not handled. Aborted!"));
		return false;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("CanAttack(true)"));
	return true;
}

//---------------------------------

void UAnimationComboComponent::SetHasHit(const bool Success)
{
	bHasHit = Success;

	if(bHasHit)
	{
		HitCounter += 1;
		
		StartTimer(HitComboTimerHandle, &UAnimationComboComponent::OnHitComboTimerTimeOut, HitComboWindowTime);
	}
}

//---------------------------------

void UAnimationComboComponent::SetAnimationState(const EAnimationState& NextState)
{
	AnimationState = NextState;
	UE_LOG(LogTemp, Warning, TEXT("StateChanged to->%s"), *UEnum::GetValueAsString(AnimationState));
}

//---------------------------------

void UAnimationComboComponent::AttackCombo(const EAnimationState& AttackInput)
{
	// What type of Attack was it ?
	switch (AttackInput)
	{
	case Melee:
		ComboInputType = EComboType::Punch;
		break;
	case Kick:
		ComboInputType = EComboType::Kick;
		break;
	case Sword:
		ComboInputType = EComboType::Sword;
		break;
	default:
		ComboInputType = EComboType::None;
		break;
	}
	UE_LOG(LogTemp, Warning, TEXT("ComboInputType->%s"), *UEnum::GetValueAsString(ComboInputType));
	
	// Do we have Combo Attacks for this type ?
	if(UAnimationDataAsset* ComboData = ComboDataAssets.FindRef(ComboInputType))
	{
		// How many Combo Sequences do we have available ?
		MaxComboCount = ComboData->GetAnimationCount();
		if(HitCounter >= MaxComboCount)
		{
			// Combo Counter is higher than possible Attack animations
			UE_LOG(LogTemp, Warning, TEXT("AttackCombo-> HitCounter(%d) ArraySize(%d)"), HitCounter, MaxComboCount);

			OnAnimNotifyComboHasEnded(true, AnimInstance->GetPlayer()->GetCurrentAnimSequence());
			return;
		}
		
			// Get the next Animation Sequence
		if(TSoftObjectPtr<UPaperZDAnimSequence> NextSequence = ComboData->Data.AnimationSequences[HitCounter])
		{
			ComboAttackOverrideAnimationSequence = NextSequence.Get();
			ComboAnimationDataType = ComboData->GetAnimationType();
			
			// Play the next Combo from our Data
			AnimInstance->PlayAnimationOverride(
				ComboAttackOverrideAnimationSequence,
				FName("DefaultSlot"),
				1.f,
				0.f,
				OnComboAttackOverrideDelegate
			);
		}
	}
	else
	{
		// Handle the case where the DataAsset is not found for the current state
		UE_LOG(LogTemp, Warning, TEXT("No DataAsset found for the current animation state(%s)"), *UEnum::GetValueAsString(ComboState));
	}
}

//---------------------------------

void UAnimationComboComponent::StartTimer(FTimerHandle& TimerHandle, void(UAnimationComboComponent::*TimerCallBack)(), float TimerDuration)
{
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		TimerCallBack,
		TimerDuration
	);
}

//---------------------------------

void UAnimationComboComponent::StopTimer(FTimerHandle& TimerHandle)
{
	SetAnimationState(Walking);
	
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

//---------------------------------

void UAnimationComboComponent::OnHitComboTimerTimeOut()
{
	SetHasHit(false);
	
	SetAnimationState(Walking);
	
	ComboState = EComboState::None;
}

//---------------------------------

void UAnimationComboComponent::OnAnimNotifyComboHasEnded(bool bHasEnded, const UPaperZDAnimSequence* LastSequencePlayed)
{
	if(bHasEnded)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnAnimNotifyComboHasEnded -> (HasEnded: %s), Sequence: %s"), 
			   bHasEnded ? TEXT("True") : TEXT("False"), 
			   *LastSequencePlayed->GetName());
		
		ComboState = EComboState::ComboEnd;

		HitCounter = 0.f;

		StartTimer(ComboCooldownTimerHandle,&UAnimationComboComponent::OnCooldownTimerTimeOut, ComboCooldownTime);
	}
}

//---------------------------------

void UAnimationComboComponent::OnCooldownTimerTimeOut()
{
	// We have just played the last Combo Sequence and waited for ComboCooldownTime
	// Start from beginning
	ComboState = EComboState::None;
	
	AnimationState = Walking;
}

//---------------------------------

void UAnimationComboComponent::OnSequenceComplete(const UPaperZDAnimSequence* AnimSequence)
{
	// Back to idle Anim, Combo Window is open
	AnimationState = Walking;

	if(HitCounter != 0)
	{
		ComboState = EComboState::Combo;
	}
	
	// Cache last Seq for Debug
	LastSequenceCompleted = AnimSequence;
	if(LastSequenceCompleted == ComboAttackOverrideAnimationSequence)
	{
		// Handle the case where the DataAsset is not found for the current state
		UE_LOG(LogTemp, Warning, TEXT("((%s) == (%s))"), *LastSequenceCompleted->GetName(), *ComboAttackOverrideAnimationSequence->GetName());
	}
}

//---------------------------------

void UAnimationComboComponent::OnSequenceChanged(const UPaperZDAnimSequence* From, const UPaperZDAnimSequence* To,
														float CurrentProgress)
{
	
}


//---------------------------------

void UAnimationComboComponent::OnComboAttackOverride(bool Completed)
{
	UE_LOG(LogTemp, Warning, TEXT("bOverrideCompleted->(%s)"), Completed ? TEXT("True") : TEXT("False"));
	
	/*
	// Override can be played, Set to Combo state
	if(HitCounter != 0)
	{
		ComboState = EComboState::Combo;
	}
	*/
}