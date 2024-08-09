// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include "Components/TextBlock.h"

//---------------------------------

void UPlayerHUD::SetLevelTxt(const float Count) const
{
	const FString Msg = FString::Printf(TEXT("LvL: %0.f - %.0f"), Count, Count);
	LevelTxt->SetText(FText::FromString(Msg));
}

//---------------------------------
void UPlayerHUD::SetCreditsTxt(const float& Amount)
{
	const FString Msg = FString::Printf(TEXT("%f"), Amount);
	CreditsTxt->SetText(FText::FromString(Msg));
}

//---------------------------------

void UPlayerHUD::SetStaminaTxt(const float& MinAmount,const float& MaxAmount)
{
	const FString Msg = FString::Printf(TEXT("SP:%0.0f/%0.0f"), MinAmount, MaxAmount);
	CreditsTxt->SetText(FText::FromString(Msg));
}

//---------------------------------

void UPlayerHUD::SetHealthTxt(const float& MinAmount,const float& MaxAmount)
{
	const FString Msg = FString::Printf(TEXT("HP:%0.0f/%0.0f"), MinAmount, MaxAmount);
	
	HealthTxt->SetText(FText::FromString(Msg));
}

