// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationComboComponent.h"
#include "PaperZDAnimInstance.h"
#include "AnimSequences/Players/PaperZDAnimPlayer.h"
#include "Project/DataAssets/AnimationDataAsset.h"
#include "Project/Player/PlayerCharacter2D.h"


UAnimationComboComponent::UAnimationComboComponent()
	:	AnimationState(),
		LastSequenceCompleted(nullptr),
		ComboState(),
		LastComboType()
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
	if(AnimInstance->GetPlayer()->GetPlaybackProgress() >= 1.f || bCanComboFromCurrentSequence)
	{
		return true;
	}
	
	UE_LOG(LogTemp, Error, TEXT("CanAttack(false), this case is not handled. Aborted!"));
	return false;
}

//---------------------------------


bool UAnimationComboComponent::TryComboAttack()
{
	if(!CanAttack())
	{
		UE_LOG(LogTemp, Error, TEXT("UAnimationComboComponent->TryComboAttack(false):State(%d) SequenceReady(%d)"), GetAnimationState(), bCanComboFromCurrentSequence);
		return false;
	}

	// Is the Combo Window Open ?
	if(bHasHit && ComboState != EComboState::ComboEnd)
	{
		// This gets stopped only if an Animation is set to Call the OnComboEndNotify
		AttackCounter += 1;
		PlayNextComboSequence(AttackCounter);
		return true;
	}
	// The ABP starts the first Animation from Changing this AnimationState
	StartComboSequence();
	return false;
}

//---------------------------------

void UAnimationComboComponent::PlayNextComboSequence(const int32 Counter)
{
	// What type of Attack was it ?
	if(UAnimationDataAsset* DataAsset = ComboDataAssets.FindRef(LastComboType))
	{
		// How many Combo Sequences do we have available ?
		int MaxComboCount = DataAsset->GetAnimationCount();

		// We can still play more Sequences
		if(AttackCounter < MaxComboCount)
		{
			// Get the next Animation Sequence
			TSoftObjectPtr<UPaperZDAnimSequence> NextSequence =
				DataAsset->Data.AnimationSequences[AttackCounter];

			if(NextSequence.IsValid())
			{
				// Play the next Combo from our Data, so we know which Data we played last
				AnimInstance->GetPlayer()->PlaySingleAnimation(NextSequence.Get(), 0.f);
			}
		}
		else
		{
			// Combo Counter is higher than possible Attack animations
			UE_LOG(LogTemp, Warning, TEXT("Triggering combo end->NO more Animations in Sequence. To set Final Combo->last animation inside the Data Asset should call AnimNotify_ComboEnd."));
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

void UAnimationComboComponent::SetAnimationState(const EAnimationState& NextState)
{
	AnimationState = NextState;

	switch (AnimationState)
	{
	case Sword:
		AnimInstance->JumpToNode(FName("JumpSword"));
		LastComboType = EComboType::Sword;
		break;
	case Walking:
		break;
	case Dashing:
		break;
	case Running:
		break;
	case Punching:
		AnimInstance->JumpToNode(FName("JumpPunch"));
		LastComboType = EComboType::Punch;
		break;
	case Kick:
		AnimInstance->JumpToNode(FName("JumpKick"));
		LastComboType = EComboType::Kick;
		break;
	case Block:
		break;
	case Grab:
		break;
	case Bow:
		break;
	case Aim:
		break;
	case Crouched:
		break;
	case GettingHit:
		break;
	case Rolling:
		break;
	default:
		break;
	}
}

//---------------------------------

void UAnimationComboComponent::StartComboSequence()
{
	ComboState = EComboState::ComboStart;
	if(AttackCounter != 0)
	{
		AttackCounter = 0;
	}
}

//---------------------------------

void UAnimationComboComponent::StartComboWindowTimer()
{
	GetWorld()->GetTimerManager().SetTimer(
		HitComboTimerHandle,
		this,
		&UAnimationComboComponent::OnHitComboTimerTimeOut,
		1.0f,
		false,
		HitComboWindowTime
	);
}

//---------------------------------
void UAnimationComboComponent::StopComboWindowTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(HitComboTimerHandle);
}

//---------------------------------

void UAnimationComboComponent::OnHitComboTimerTimeOut()
{
	SetHasHit(false);
}

//---------------------------------

void UAnimationComboComponent::OnAnimNotifyComboHasEnded(bool bHasEnded, const UPaperZDAnimSequence* LastSequencePlayed)
{
	if(bHasEnded)
	{
		ComboState = EComboState::ComboEnd;
		AttackCounter = 0.f;

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
	ComboState = EComboState::ComboStart;
	if(AttackCounter != 0.f)
	{
		AttackCounter = 0.f;
	}
}

//---------------------------------

void UAnimationComboComponent::OnSequenceComplete(const UPaperZDAnimSequence* AnimSequence)
{
	
}

//---------------------------------

void UAnimationComboComponent::OnSequenceChanged(const UPaperZDAnimSequence* From, const UPaperZDAnimSequence* To,
														float CurrentProgress)
{
	
}
