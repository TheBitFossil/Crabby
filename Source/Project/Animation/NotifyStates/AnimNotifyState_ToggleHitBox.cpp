// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_ToggleHitBox.h"

#include "PaperZDAnimInstance.h"
#include "Project/Player/PlayerCharacter2D.h"


void UAnimNotifyPlayerAttack::TickNotify(float DeltaTime, float Playtime, float LastPlaybackTime,
                                         UPrimitiveComponent* AnimRenderComponent, bool& bPersistentActiveState, UPaperZDAnimInstance* OwningInstance) const
{
	Super::TickNotify(DeltaTime, Playtime, LastPlaybackTime, AnimRenderComponent, bPersistentActiveState, OwningInstance);
}

//---------------------------------

void UAnimNotifyPlayerAttack::OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyBegin_Implementation(OwningInstance);

	if(!OwningInstance || !Player2D)
	{
		return;
	}
		
	Player2D->ToggleAttackCollisionBox(true);
}

//---------------------------------

void UAnimNotifyPlayerAttack::OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyEnd_Implementation(OwningInstance);
	if(!OwningInstance || !Player2D)
	{
		return;
	}
	Player2D->ToggleAttackCollisionBox(false);
}

//---------------------------------

void UAnimNotifyPlayerAttack::OnNotifyAborted(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyAborted(OwningInstance);

	if(!OwningInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Owning Instance is nullptr in OnNotifyAborted"));
		return;
	}

	if(!Player2D)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Failed to retrieve Player2D from BaseNotifyState in OnNotifyAborted."));
		return;
	}

	Player2D->ToggleAttackCollisionBox(false);
}
