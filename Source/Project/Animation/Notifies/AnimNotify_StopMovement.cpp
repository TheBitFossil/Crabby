// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_StopMovement.h"
#include "AnimSequences/Players/PaperZDAnimPlayer.h"
#include "Project/Player/PlayerCharacter2D.h"

UAnimNotify_StopMovement::UAnimNotify_StopMovement()
{
}

//---------------------------------

void UAnimNotify_StopMovement::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnReceiveNotify_Implementation(OwningInstance);

	if(!OwningInstance)
	{
		return;
	}

	if(!OwningInstance->GetPlayer()->GetCurrentAnimSequence())
	{
		UE_LOG(LogTemp, Warning, TEXT("UAnimNotify_StopMovement->NO AnimSequence"));
		return;
	}
	
	if(APlayerCharacter2D* OwningActor = Cast<APlayerCharacter2D>(OwningInstance->GetOwningActor()))
	{
		OwningActor->OnIsMovementAllowed(false);
	}
	UE_LOG(LogTemp, Error, TEXT("UAnimNotify_StopMovement->NO Owning Actor!"));
}

//---------------------------------

void UAnimNotify_StopMovement::OnNotifyAborted(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyAborted(OwningInstance);
	
	if(!OwningInstance)
	{
		return;
	}

	if(!OwningInstance->GetPlayer()->GetCurrentAnimSequence())
	{
		UE_LOG(LogTemp, Warning, TEXT("UAnimNotify_StopMovement->NO AnimSequence"));
		return;
	}
	
	if(APlayerCharacter2D* OwningActor = Cast<APlayerCharacter2D>(OwningInstance->GetOwningActor()))
	{
		OwningActor->OnIsMovementAllowed(false);
	}
	UE_LOG(LogTemp, Error, TEXT("UAnimNotify_StopMovement->NO Owning Actor!"));
}

//---------------------------------

void UAnimNotify_StopMovement::TickNotify(float DeltaTime, float Playtime, float LastPlaybackTime,
	UPrimitiveComponent* AnimRenderComponent, bool& bPersistentActiveState, UPaperZDAnimInstance* OwningInstance) const
{
	Super::TickNotify(DeltaTime, Playtime, LastPlaybackTime, AnimRenderComponent, bPersistentActiveState, OwningInstance);
}
