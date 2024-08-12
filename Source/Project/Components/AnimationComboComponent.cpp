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
	// Is Current State hindering our Ability ?
	if(GetAnimationState() == Dashing || ComboState == EComboState::ComboEnd)
	{
		return false;
	}
	
	// Is Animation Over or Is Animation ready for Combo transition
	//UE_LOG(LogTemp, Error, TEXT("CanAttack(false), this case is not handled. Aborted!"));
	return true;
}

//---------------------------------


void UAnimationComboComponent::ComboAttack()
{
	if(!CanAttack())
	{
		UE_LOG(LogTemp, Error, TEXT("UAnimationComboComponent->TryComboAttack(false):State(%d) SequenceReady(%d)"), GetAnimationState(), bCanComboFromCurrentSequence);
		return;
	}

	// Is the Combo Window Open ?
	if(bHasHit)
	{
		// This gets stopped only if an Animation is set to Call the OnComboEndNotify
		PlayNextComboSequence();
	}
}

//---------------------------------

void UAnimationComboComponent::SetHasHit(const bool Success)
{
	bHasHit = Success;

	if(bHasHit)
	{
		HitCounter += 1;
		
		StartComboWindowTimer();
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

	// Do we have Combo Attacks for this type ?
	if(UAnimationDataAsset* ComboData = ComboDataAssets.FindRef(ComboInputType))
	{
		// How many Combo Sequences do we have available ?
		MaxComboCount = ComboData->GetAnimationCount();
		if(HitCounter <= MaxComboCount)
		{
			// Get the next Animation Sequence
			TSoftObjectPtr<UPaperZDAnimSequence> NextSequence =
				ComboData->Data.AnimationSequences[HitCounter];

			if(NextSequence.IsValid())
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
			// Combo Counter is higher than possible Attack animations
			UE_LOG(LogTemp, Warning, TEXT("AttackCombo-> HitCounter(%f) ArraySize(%f"), HitCounter, MaxComboCount);
			OnAnimNotifyComboHasEnded(true, AnimInstance->GetPlayer()->GetCurrentAnimSequence());
		}
	}
	else
	{
		// Handle the case where the DataAsset is not found for the current state
		UE_LOG(LogTemp, Warning, TEXT("No DataAsset found for the current animation state"));
	}
}

//---------------------------------

void UAnimationComboComponent::StartComboWindowTimer()
{
	GetWorld()->GetTimerManager().SetTimer(
		HitComboTimerHandle,
		this,
		&UAnimationComboComponent::OnHitComboTimerTimeOut,
		HitComboWindowTime,
		false
	);
}

//---------------------------------
void UAnimationComboComponent::StopComboWindowTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(HitComboTimerHandle);
	AnimationState = Walking;
}

//---------------------------------

void UAnimationComboComponent::OnHitComboTimerTimeOut()
{
	SetHasHit(false);
	
	AnimationState = Walking;

	ComboState = EComboState::None;
}

//---------------------------------

void UAnimationComboComponent::OnAnimNotifyComboHasEnded(bool bHasEnded, const UPaperZDAnimSequence* LastSequencePlayed)
{
	if(bHasEnded)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnAnimNotifyComboHasEnded->(HasEnded(%d), Sequence->(%s)"), bHasEnded, *LastSequencePlayed);
		ComboState = EComboState::ComboEnd;

		HitCounter = 0.f;

		GetWorld()->GetTimerManager().SetTimer(
			ComboCooldownTimerHandle,
			this,
			&UAnimationComboComponent::OnCooldownTimerTimeOut,
			1.f,
			false,
			ComboCooldownTime
		);
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
}

//---------------------------------

void UAnimationComboComponent::OnSequenceChanged(const UPaperZDAnimSequence* From, const UPaperZDAnimSequence* To,
														float CurrentProgress)
{
	
}


//---------------------------------

void UAnimationComboComponent::OnComboAttackOverride(bool Completed)
{
	if(!Completed)
	{
		UE_LOG(LogTemp, Error, TEXT("OnComboAttackOverride->Error Override not comleted."));
	}
	
	// Override can be played, Set to Combo state
	if(HitCounter != 0)
	{
		ComboState = EComboState::Combo;
	}
}