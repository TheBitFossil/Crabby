// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationComboComponent.h"
#include "PaperZDAnimInstance.h"

#include "Project/Player/PlayerCharacter2D.h"


UAnimationComboComponent::UAnimationComboComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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
		}
	}
}


void UAnimationComboComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//---------------------------------

void UAnimationComboComponent::ChangeAnimation(const EAnimationState& AnimationState)
{
	switch (AnimationState)
	{
	case EAnimationState::Sword:
		AnimInstance->JumpToNode(FName("JumpSword"));
		break;
	case EAnimationState::Walking:
		break;
	case EAnimationState::Dashing:
		break;
	case EAnimationState::Running:
		break;
	case EAnimationState::Punch:
		AnimInstance->JumpToNode(FName("JumpPunch"));
		break;
	case EAnimationState::Kick:
		AnimInstance->JumpToNode(FName("JumpKick"));
		break;
	case EAnimationState::Block:
		break;
	case EAnimationState::Grab:
		break;
	case EAnimationState::Bow:
		break;
	case EAnimationState::Aim:
		break;
	case EAnimationState::Crouching:
		break;
	case EAnimationState::GettingHit:
		break;
	case EAnimationState::Rolling:
		break;
	}
	/*
	UPaperZDAnimSequence* NextAttackAnimation = nullptr;
	if(AttackAnimationDataAsset)
	{
		AttackAnimationDataAsset->ChooseAttackAnimation(AnimationState, AnimationComboComponent->AttackCounter);
	}

	GetAnimInstance()->PlayAnimationOverride(
			AttackAnimationSequence,
			FName("DefaultSlot"),
			1,
			0,
			OnAttackOverrideEndDelegate
		);
		*/
}

