// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECT_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> DiamondsTxt;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
    TObjectPtr<UTextBlock> DashCoolDownTxt;
    	
    UPROPERTY(EditAnywhere, meta = (BindWidget))
    TObjectPtr<UTextBlock> LevelTxt;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthTxt;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthProgressBarInstant;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthProgressBarDelayed;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> DashProgressBar;
	
	void SetDiamonds(const int Amount) const;
	void SetDashCoolDown(const float Value) const;
	void SetLevel(const int Count) const;
	void SetHealth(const int Amount) const;
	
};
