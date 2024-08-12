// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_DashEnded.h"

#include "Project/Player/PlayerCharacter2D.h"
UAnimNotify_DashEnded::UAnimNotify_DashEnded()
{
}

//---------------------------------

void UAnimNotify_DashEnded::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnReceiveNotify_Implementation(OwningInstance);

	if(!OwningInstance || !Player2D)
	{
		return;
	}
	
	Player2D->OnAnimNotifyDashEnded();
}

//---------------------------------

void UAnimNotify_DashEnded::OnNotifyAborted(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyAborted(OwningInstance);
}

//---------------------------------

void UAnimNotify_DashEnded::TickNotify(float DeltaTime, float Playtime, float LastPlaybackTime,
	UPrimitiveComponent* AnimRenderComponent, bool& bPersistentActiveState, UPaperZDAnimInstance* OwningInstance) const
{
	Super::TickNotify(DeltaTime, Playtime, LastPlaybackTime, AnimRenderComponent, bPersistentActiveState, OwningInstance);
}
