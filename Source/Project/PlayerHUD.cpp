// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include "Components/TextBlock.h"

void UPlayerHUD::SetDiamonds(const int Amount) const
{
	const FString Msg = FString::Printf(TEXT("Diamonds: %d"), Amount);
	DiamondsTxt->SetText(FText::FromString(Msg));
}

//---------------------------------

void UPlayerHUD::SetDashCoolDown(const float Value) const
{
	const FString Msg = FString::Printf(TEXT("Dash ready in: %f"), Value);
	DashCoolDownTxt->SetText(FText::FromString(Msg));
}

//---------------------------------

void UPlayerHUD::SetLevel(const int Count) const
{
	const FString Msg = FString::Printf(TEXT("LvL: %d"), Count);
	LevelTxt->SetText(FText::FromString(Msg));
}

//---------------------------------

void UPlayerHUD::SetHealth(const int Amount) const
{
	const FString Msg = FString::Printf(TEXT("HP: %d"), Amount);
	HealthTxt->SetText(FText::FromString(Msg));
}
