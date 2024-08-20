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

	if(!OwningInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("UAnimNotifyPlayerAttack->OnNotifyBegin_Implementation: No OwningInstance!"));
		return;
	}

	// TODO:: Make a base class, if you want to call the same notifies for different classes
	if(APlayerCharacter2D* OwningActor = Cast<APlayerCharacter2D>(OwningInstance->GetOwningActor()))
	{
		OwningActor->ToggleAttackCollisionBox(true);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UAnimNotifyPlayerAttack->OnNotifyBegin_Implementation:NO Owning Actor!"));
	}
}

//---------------------------------

void UAnimNotifyPlayerAttack::OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyEnd_Implementation(OwningInstance);
	
	if(!OwningInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("UAnimNotifyPlayerAttack->OnNotifyEnd_Implementation: No OwningInstance!"));
		return;
	}

	if(APlayerCharacter2D* OwningActor = Cast<APlayerCharacter2D>(OwningInstance->GetOwningActor()))
	{
		OwningActor->ToggleAttackCollisionBox(false);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UAnimNotifyPlayerAttack->OnNotifyEnd_Implementation:NO Owning Actor!"));
	}
}

//---------------------------------

void UAnimNotifyPlayerAttack::OnNotifyAborted(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyAborted(OwningInstance);

	if(!OwningInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("UAnimNotifyPlayerAttack->OnNotifyAborted: No OwningInstance!"));
		return;
	}

	if(APlayerCharacter2D* OwningActor = Cast<APlayerCharacter2D>(OwningInstance->GetOwningActor()))
	{
		OwningActor->ToggleAttackCollisionBox(false);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UAnimNotifyPlayerAttack->OnNotifyAborted:NO Owning Actor!"));
	}
}
