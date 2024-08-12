// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_Dashing.h"

#include "Project/Player/PlayerCharacter2D.h"


UAnimNotifyState_Dashing::UAnimNotifyState_Dashing()
{
}

//---------------------------------

void UAnimNotifyState_Dashing::TickNotify(float DeltaTime, float Playtime, float LastPlaybackTime,
                                          UPrimitiveComponent* AnimRenderComponent, bool& bPersistentActiveState, UPaperZDAnimInstance* OwningInstance) const
{
	Super::TickNotify(DeltaTime, Playtime, LastPlaybackTime, AnimRenderComponent, bPersistentActiveState, OwningInstance);
}

//---------------------------------


void UAnimNotifyState_Dashing::OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyEnd_Implementation(OwningInstance);
	if(!OwningInstance || !Player2D)
	{
		return;
	}
	
	Player2D->OnAnimNotifyDashEnded();
}
