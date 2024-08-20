// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_DashEnded.h"
#include "AnimSequences/Players/PaperZDAnimPlayer.h"
#include "Project/Player/PlayerCharacter2D.h"

UAnimNotify_DashEnded::UAnimNotify_DashEnded()
{
}

//---------------------------------

void UAnimNotify_DashEnded::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnReceiveNotify_Implementation(OwningInstance);

	if(!OwningInstance)
	{
		return;
	}

	if(!OwningInstance->GetPlayer()->GetCurrentAnimSequence())
	{
		UE_LOG(LogTemp, Warning, TEXT("UAnimNotify_DashEnded->NO AnimSequence"));
		return;
	}
	
	if(APlayerCharacter2D* OwningActor = Cast<APlayerCharacter2D>(OwningInstance->GetOwningActor()))
	{
		OwningActor->OnAnimNotifyDashEnded();
	}
	UE_LOG(LogTemp, Error, TEXT("UAnimNotify_DashEnded->NO Owning Actor!"));
	
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
