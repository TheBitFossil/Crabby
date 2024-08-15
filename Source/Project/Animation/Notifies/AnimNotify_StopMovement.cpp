// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_StopMovement.h"

#include "Project/Player/PlayerCharacter2D.h"
UAnimNotify_StopMovement::UAnimNotify_StopMovement()
{
}

//---------------------------------

void UAnimNotify_StopMovement::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnReceiveNotify_Implementation(OwningInstance);

	Player2D->OnIsMovementAllowed(false);
}

//---------------------------------

void UAnimNotify_StopMovement::OnNotifyAborted(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyAborted(OwningInstance);
}

//---------------------------------

void UAnimNotify_StopMovement::TickNotify(float DeltaTime, float Playtime, float LastPlaybackTime,
	UPrimitiveComponent* AnimRenderComponent, bool& bPersistentActiveState, UPaperZDAnimInstance* OwningInstance) const
{
	Super::TickNotify(DeltaTime, Playtime, LastPlaybackTime, AnimRenderComponent, bPersistentActiveState, OwningInstance);
}
