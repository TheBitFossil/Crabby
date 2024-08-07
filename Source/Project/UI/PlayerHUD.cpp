// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include "Components/TextBlock.h"

void UPlayerHUD::SetCreditsTxt(const int Amount) const
{
	const FString Msg = FString::Printf(TEXT("Diamonds: %d"), Amount);
	CreditsTxt->SetText(FText::FromString(Msg));
}

//---------------------------------

void UPlayerHUD::SetLevelTxt(const int Count) const
{
	const FString Msg = FString::Printf(TEXT("LvL: %d"), Count);
	LevelTxt->SetText(FText::FromString(Msg));
}
