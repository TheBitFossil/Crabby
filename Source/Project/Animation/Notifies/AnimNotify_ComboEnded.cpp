// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ComboEnded.h"

#include "AnimSequences/Players/PaperZDAnimPlayer.h"
#include "Project/Components/AnimationComboComponent.h"

UAnimNotify_ComboEnded::UAnimNotify_ComboEnded()
{
}

//---------------------------------

void UAnimNotify_ComboEnded::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnReceiveNotify_Implementation(OwningInstance);

	if(!OwningInstance || !ComboComponent)
	{
		return;
	}

	if(!OwningInstance->GetPlayer()->GetCurrentAnimSequence())
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning->NO Anim Sequence"));
		return;
	}
	ComboComponent->OnAnimNotifyComboHasEnded(true, OwningInstance->GetPlayer()->GetCurrentAnimSequence());
}

//---------------------------------

void UAnimNotify_ComboEnded::OnNotifyAborted(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyAborted(OwningInstance);
	
	ComboComponent->OnAnimNotifyComboHasEnded(true, OwningInstance->GetPlayer()->GetCurrentAnimSequence());
	UE_LOG(LogTemp, Error, TEXT("ErrorNumber->ComboComponent, ComboSequenceHasEnded->Aborted"));
}

//---------------------------------

void UAnimNotify_ComboEnded::TickNotify(float DeltaTime, float Playtime, float LastPlaybackTime,
	UPrimitiveComponent* AnimRenderComponent, bool& bPersistentActiveState, UPaperZDAnimInstance* OwningInstance) const
{
	Super::TickNotify(DeltaTime, Playtime, LastPlaybackTime, AnimRenderComponent, bPersistentActiveState, OwningInstance);
}