// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Base.h"

#include "Project/Player/PlayerCharacter2D.h"
UAnimNotify_Base::UAnimNotify_Base()
{
	ComboComponent = nullptr;
}

//---------------------------------

void UAnimNotify_Base::InitComponents(APlayerCharacter2D* OwningActor) const
{
	if(!OwningActor)
	{
		return;
	}

	Player2D = OwningActor;
	if(!ComboComponent)
	{
		ComboComponent = Player2D->GetComboComponent();
		UE_LOG(LogTemp, Warning, TEXT("InitComponents->Init Component by Notify Base Class (%s)"), *ComboComponent.GetName());
	}
	UE_LOG(LogTemp, Error, TEXT("InitComponents->NO COMBO COMPONENT!"));
}

//---------------------------------

void UAnimNotify_Base::TickNotify(float DeltaTime, float Playtime, float LastPlaybackTime,
                                  UPrimitiveComponent* AnimRenderComponent, bool& bPersistentActiveState, UPaperZDAnimInstance* OwningInstance) const
{
	Super::TickNotify(DeltaTime, Playtime, LastPlaybackTime, AnimRenderComponent, bPersistentActiveState, OwningInstance);
}

//---------------------------------

void UAnimNotify_Base::OnNotifyAborted(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyAborted(OwningInstance);
}

//---------------------------------

void UAnimNotify_Base::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnReceiveNotify_Implementation(OwningInstance);

	if (!OwningInstance)
	{
		return;
	}

	if (APlayerCharacter2D* OwningActor = Cast<APlayerCharacter2D>(OwningInstance->GetOwningActor()))
	{
		InitComponents(OwningActor);
	}
}
