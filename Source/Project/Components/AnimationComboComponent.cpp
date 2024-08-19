// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationComboComponent.h"
#include "AnimSequences/Players/PaperZDAnimPlayer.h"

UAnimationComboComponent::UAnimationComboComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

//---------------------------------

void UAnimationComboComponent::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerCharacter2D = Cast<APlayerCharacter2D>(GetOwner());
	if(PlayerCharacter2D)
	{
		AnimInstance = Cast<UPaperZDAnimInstance>(PlayerCharacter2D->GetAnimInstance());
		if(AnimInstance)
		{
			// ...
			AnimInstance->GetPlayer()->OnPlaybackSequenceComplete.AddDynamic(this, &UAnimationComboComponent::OnSequenceComplete);
			AnimInstance->GetPlayer()->OnPlaybackSequenceChanged.AddDynamic(this, &UAnimationComboComponent::OnSequenceChanged);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AnimInstance is not valid."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter2D is not valid."));
	}
		
	OnComboAttackOverrideDelegate.BindUObject(this, &UAnimationComboComponent::OnComboAttackOverride);
}

//---------------------------------

void UAnimationComboComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

//---------------------------------

bool UAnimationComboComponent::CanAttack()
{
	if(AnimInstance->GetPlayer()->IsPlaying() && AnimInstance->GetPlayer()->GetCurrentAnimSequence() == ComboDataAnimSequence)
	{
		UE_LOG(LogTemp, Warning, TEXT("CanAttack->Failed: Sequence playing(%s)"), *ComboDataAnimSequence->GetName());
		return false;
	}

	// Is any Current State hindering our Ability ?
	if(!bHasLastComboSequenceCompleted || AnimationState == ECurrentAnimStates::Attacking)
	{
		UE_LOG(LogTemp, Warning, TEXT("CanAttack->Failed!CanCombo(%s) AnimState(%s)"),
		bOverrideCompleted ? TEXT("True") : TEXT("False"), bHasLastComboSequenceCompleted ? TEXT("True") : TEXT("False"));

		return false;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("CanAttack->bOverrideCompleted: (%s), bCanComboFromCurrentSequence:(%s)"), 
		bOverrideCompleted ? TEXT("True") : TEXT("False"), bHasLastComboSequenceCompleted ? TEXT("True") : TEXT("False"));

	return true;
}

//---------------------------------

void UAnimationComboComponent::CalculateAttackDamage(const float InDamage)
{
	AttackDamageCurrentHit = InDamage;
}

//---------------------------------


void UAnimationComboComponent::CalculateAttackCost(const float InCost)
{
	AttackCostCurrentHit = InCost;
}

//---------------------------------

float UAnimationComboComponent::GetAttackDamage()
{
	return AttackDamageCurrentHit;
}

//---------------------------------

//---------------------------------

void UAnimationComboComponent::SetHasHit(const bool Success)
{
	bHasHit = Success;

	if(bHasHit)
	{
		IncreaseHitCounter(1);
		IncreaseComboCount(1);
		if(HitComboWindowTime > 0.f)
		{
			UE_LOG(LogTemp, Warning, TEXT("SetHasHit"));
			StartTimer(HitComboTimerHandle, &UAnimationComboComponent::OnHitComboTimerTimeOut, HitComboWindowTime);
		}
	}
}

//---------------------------------

void UAnimationComboComponent::SetAnimationState(const ECurrentAnimStates NextState)
{
	if(AnimationState != NextState)
	{
		AnimationState = NextState;
		UE_LOG(LogTemp, Warning, TEXT("SetAnimationState To->(%s)"), *UEnum::GetValueAsString(AnimationState));
	}
}

//---------------------------------

void UAnimationComboComponent::RequestAttackCombo(const EComboType& InputAttackType)
{
	// Check if we can pay for this attack with stamina
	if((ComboDataAssetKey = ComboDataAssets.FindRef(InputAttackType)))
	{
		if(UPlatformerGameInstance* GameInstance = Cast<UPlatformerGameInstance>(PlayerCharacter2D->GetGameInstance()))
		{
			const float StaminaCosts = ComboDataAssetKey->Data.AnimationCost;
			if(GameInstance->GetStamina() > StaminaCosts)
			{
				PlayerCharacter2D->RemoveStamina(StaminaCosts);

				CalculateAttackDamage(ComboDataAssetKey->Data.AnimationDamage);
				CalculateAttackCost(ComboDataAssetKey->Data.AnimationCost);

				PlayerCharacter2D->OnIsMovementAllowed(false);								// Stop Moving during an Attack
				
				StartAttackCombo(InputAttackType);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Not enough Stamina to pay for attack."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No viable GameInstance found inside PlayerCharacter2D."));
		}
	}
}

//---------------------------------

void UAnimationComboComponent::StartAttackCombo(const EComboType& InputAttackType)
{
	// Do we have Combo Attacks for this type ?
	LastComboInputType = InputAttackType;
	
	UE_LOG(LogTemp, Warning, TEXT("AttackCombo:HitCounter->Before next Anim(%d)"), HitCounter);

	// Do we have enough Sequences to choose from "3" same as Combo Count (0,1,2)
	if(ComboDataAssetKey->Data.AnimationSequences.IsValidIndex(HitCounter))
	{
		if(TSoftObjectPtr<UPaperZDAnimSequence> NextSequence = ComboDataAssetKey->Data.AnimationSequences[HitCounter])
		{
			if((ComboDataAnimSequence = NextSequence.Get()))
			{
				UE_LOG(LogTemp, Warning, TEXT("NextComboSequence->(%s)"), *ComboDataAnimSequence->GetName());

				SetAnimationState(ECurrentAnimStates::Attacking);
				
				AnimInstance->PlayAnimationOverride(ComboDataAnimSequence,FName("DefaultSlot"),
					1.f, 0.f, OnComboAttackOverrideDelegate);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("ComboDataAnimSequence is invalid-"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("NextSequence is invalid."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AttackCombo-> HitCounter(%d) ArraySize(%d)"), HitCounter, MaxComboCount);
		OnAnimNotifyComboHasEnded(true, AnimInstance->GetPlayer()->GetCurrentAnimSequence());
	}
	
	// Right now: Damage is the Damage for all attacks inside A Data Asset
	// We can not change it for each Sequence without 
	// TODO:: Use more data packages inside packages for each animation
	// then we can define their values and everything we need for transitions

	// TODO:: Think about making a template Combo State, that gets filled
	// with the necessary animations inside the ABP. This would lead to
	// less micro managing
	// TODO:: We can set our Combo Counter, and Hit Counter, this will change the ABP
	// TODO:: The ABP is prefilled with our possible Combos
}

//---------------------------------

void UAnimationComboComponent::StartTimer(FTimerHandle& TimerHandle, void(UAnimationComboComponent::*TimerCallBack)(), float TimerDuration)
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			this,
			TimerCallBack,
			TimerDuration
		);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GetWorld() returned nullptr."));
	}
}
//---------------------------------

void UAnimationComboComponent::OnHitComboTimerTimeOut()
{
	SetHasHit(false);
	
	SetAnimationState(ECurrentAnimStates::Walking);

	ResetHitCounter();
}

//---------------------------------

void UAnimationComboComponent::OnAnimNotifyComboHasEnded(bool bHasEnded, const UPaperZDAnimSequence* LastSequencePlayed)
{
	if(!LastSequencePlayed || !GetWorld())
	{
		return;
	}

	FString SequenceName = LastSequencePlayed ? LastSequencePlayed->GetName() : TEXT("None");
	UE_LOG(LogTemp, Warning, TEXT("OnAnimNotifyComboHasEnded ->(HasEnded: %s), Sequence: (%s)"), 
		   bHasEnded ? TEXT("True") : TEXT("False"), *SequenceName);
	
	if (bHasEnded)
	{
		ResetHitCounter();
		
		// Check TimerManager
		UWorld* World = GetWorld();
		FTimerManager* TimerMgr = &World->GetTimerManager();
		if (TimerMgr)
		{
			UE_LOG(LogTemp, Warning, TEXT("TimerManager is valid."));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("TimerManager is nullptr."));
		}
	}
}

//---------------------------------

void UAnimationComboComponent::OnCooldownTimerTimeOut()
{
	// We have just played the last Combo Sequence and waited for ComboCooldownTime
	SetAnimationState(ECurrentAnimStates::Walking);
}

//---------------------------------

void UAnimationComboComponent::OnSequenceComplete(const UPaperZDAnimSequence* AnimSequence)
{
	if(!AnimSequence)
	{
		return;
	}
	
	LastAnimSequenceCompleted = AnimSequence;
	UE_LOG(LogTemp, Warning, TEXT("OnSequenceComplete->Last AnimSeq(%s)"), *AnimSequence->GetName());
	if(LastAnimSequenceCompleted == ComboDataAnimSequence)
	{
		ResetComboSequence(LastAnimSequenceCompleted);
	}

	PlayerCharacter2D->OnIsMovementAllowed(true);
	SetAnimationState(ECurrentAnimStates::Walking);
}

//---------------------------------

void UAnimationComboComponent::ResetComboSequence(const UPaperZDAnimSequence* FromAnimSequence, const UPaperZDAnimSequence* ToAnimSequence)
{
	if(!FromAnimSequence)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("ResetComboSequence->From(%s)"), *FromAnimSequence->GetName());
	PlayerCharacter2D->OnIsMovementAllowed(true);

	bHasLastComboSequenceCompleted = true;
	UE_LOG(LogTemp, Warning, TEXT("OnSequenceComplete->Move Allowed after Combo SeqCompleted(%s)"), *ComboDataAnimSequence->GetName());
	UE_LOG(LogTemp, Warning, TEXT("ResetComboSequence: Last Combat Input(%s)"), *UEnum::GetValueAsString(LastComboInputType));
	if(LastComboInputType != EComboType::None)
	{
		LastComboInputType = EComboType::None;
		
		UE_LOG(LogTemp, Warning, TEXT("ResetComboSequence->NO Combat Input(%s)"), *UEnum::GetValueAsString(LastComboInputType));
	}
	
	if(ToAnimSequence)
	{
		UE_LOG(LogTemp, Warning, TEXT("ResetComboSequence->To(%s)"), *ToAnimSequence->GetName());
	}
}

//---------------------------------

void UAnimationComboComponent::OnSequenceChanged(const UPaperZDAnimSequence* From, const UPaperZDAnimSequence* To,
														float CurrentProgress)
{
	if(!From || !To)
	{
		return;
	}
	
	if(From == ComboDataAnimSequence)
	{
		UE_LOG(LogTemp, Error, TEXT("OnSequenceChanged-> Combo changed From(%s) To(%s)."), *To->GetName(), *From->GetName());
		ResetComboSequence(From, To);
	}
	
}

//---------------------------------

void UAnimationComboComponent::OnComboAttackOverride(bool Completed)
{
	if(Completed)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnComboAttackOverrideCompleted->Success"));
		bOverrideCompleted = Completed;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnComboAttackOverrideCompleted->Failed"));
	}
}