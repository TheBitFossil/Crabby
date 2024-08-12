// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyStateBase.h"
#include "PaperZDAnimInstance.h"
#include "Project/Player/PlayerCharacter2D.h"


UAnimNotifyStateBase::UAnimNotifyStateBase()
{
	ComboComponent = nullptr;
}

//---------------------------------

void UAnimNotifyStateBase::TickNotify(float DeltaTime, float Playtime, float LastPlaybackTime,
                                      UPrimitiveComponent* AnimRenderComponent, bool& bPersistentActiveState, UPaperZDAnimInstance* OwningInstance) const
{
	Super::TickNotify(DeltaTime, Playtime, LastPlaybackTime, AnimRenderComponent, bPersistentActiveState, OwningInstance);
}

//---------------------------------

void UAnimNotifyStateBase::InitComponents(APlayerCharacter2D* Player) const
{
	if(!Player)
	{
		return;
	}

	Player2D = Player;
	if(!ComboComponent)
	{
		ComboComponent = Player2D->GetComboComponent();
	}
}

//---------------------------------

void UAnimNotifyStateBase::OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyBegin_Implementation(OwningInstance);

	if (!OwningInstance)
	{
		return;
	}

	if (APlayerCharacter2D* OwningActor = Cast<APlayerCharacter2D>(OwningInstance->GetOwningActor()))
	{
		InitComponents(OwningActor);
	}
}

//---------------------------------

void UAnimNotifyStateBase::OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyEnd_Implementation(OwningInstance);
	
	
}

//---------------------------------

void UAnimNotifyStateBase::OnNotifyAborted(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyAborted(OwningInstance);
	
}
