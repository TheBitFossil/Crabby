// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ComboEnded.h"

#include "PaperZDAnimInstance.h"
#include "AnimSequences/Players/PaperZDAnimPlayer.h"
#include "Project/Player/PlayerCharacter2D.h"

UAnimNotify_ComboEnded::UAnimNotify_ComboEnded()
{
}

//---------------------------------

void UAnimNotify_ComboEnded::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnReceiveNotify_Implementation(OwningInstance);

	if(!OwningInstance)
	{
		return;
	}

	if(!OwningInstance->GetPlayer()->GetCurrentAnimSequence())
	{
		UE_LOG(LogTemp, Warning, TEXT("UAnimNotify_ComboEnded->NO AnimSequence"));
		return;
	}

	if(APlayerCharacter2D* OwningActor = Cast<APlayerCharacter2D>(OwningInstance->GetOwningActor()))
	{
		OwningActor->OnAnimNotifyComboHasEnded(true, OwningInstance->GetPlayer()->GetCurrentAnimSequence());
		return;
	}
	
	UE_LOG(LogTemp, Error, TEXT("UAnimNotify_ComboEnded->NO Owning Actor!"));
}

//---------------------------------

void UAnimNotify_ComboEnded::OnNotifyAborted(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyAborted(OwningInstance);

	if(!OwningInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("UAnimNotify_ComboEnded->NO OwningInstance!"));
		return;
	}

	if(!OwningInstance->GetPlayer()->GetCurrentAnimSequence())
	{
		UE_LOG(LogTemp, Warning, TEXT("UAnimNotify_ComboEnded->NO AnimSequence"));
		return;
	}
	
	if(APlayerCharacter2D* OwningActor = Cast<APlayerCharacter2D>(OwningInstance->GetOwningActor()))
	{
		OwningActor->OnAnimNotifyComboHasEnded(true, OwningInstance->GetPlayer()->GetCurrentAnimSequence());
	}
	UE_LOG(LogTemp, Error, TEXT("UAnimNotify_ComboEnded->NO Owning Actor!"));
}

//---------------------------------

void UAnimNotify_ComboEnded::TickNotify(float DeltaTime, float Playtime, float LastPlaybackTime,
	UPrimitiveComponent* AnimRenderComponent, bool& bPersistentActiveState, UPaperZDAnimInstance* OwningInstance) const
{
	Super::TickNotify(DeltaTime, Playtime, LastPlaybackTime, AnimRenderComponent, bPersistentActiveState, OwningInstance);
}
