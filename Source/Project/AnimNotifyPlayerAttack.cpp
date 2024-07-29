// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyPlayerAttack.h"

#include "PaperZDAnimInstance.h"
#include "PlayerCharacter2D.h"


void UAnimNotifyPlayerAttack::TickNotify(float DeltaTime, float Playtime, float LastPlaybackTime,
	UPrimitiveComponent* AnimRenderComponent, bool& bPersistentActiveState, UPaperZDAnimInstance* OwningInstance) const
{
	Super::TickNotify(DeltaTime, Playtime, LastPlaybackTime, AnimRenderComponent, bPersistentActiveState, OwningInstance);
}

//---------------------------------

void UAnimNotifyPlayerAttack::OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyBegin_Implementation(OwningInstance);

	if(!OwningInstance)
	{
		return;
	}
	
	if (APlayerCharacter2D* OwningActor = Cast<APlayerCharacter2D>(OwningInstance->GetOwningActor()))
	{
		OwningActor->ToggleAttackCollisionBox(true);
	}
}

//---------------------------------

void UAnimNotifyPlayerAttack::OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyEnd_Implementation(OwningInstance);
	if(!OwningInstance)
	{
		return;
	}
	
	if (APlayerCharacter2D* OwningActor = Cast<APlayerCharacter2D>(OwningInstance->GetOwningActor()))
	{
		OwningActor->ToggleAttackCollisionBox(false);
	}
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

	APlayerCharacter2D* OwningActor = Cast<APlayerCharacter2D>(OwningInstance->GetOwningActor());
	if(!OwningActor)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Failed to cast OwningInstance->GetOwningActor() to APlayerCharacter2D in OnNotifyAborted."));
		return;
	}

	OwningActor->ToggleAttackCollisionBox(false);
}
