// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHUD.h"
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
	TObjectPtr<UTextBlock> CreditsTxt;
	    	
    UPROPERTY(EditAnywhere, meta = (BindWidget))
    TObjectPtr<UTextBlock> LevelTxt;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthTxt;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthProgressBarInstant;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthProgressBarDelayed;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> StaminaTxt;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> StaminaProgressBarInstant;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> StaminaProgressBarDelayed;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> DashProgressBar;

	void SetLevelTxt(const float Count) const;
	
	void SetCreditsTxt(const float& Amount);
	
	void SetStaminaTxt(const float& MinAmount, const float& MaxAmount);
	
	void SetHealthTxt(const float& MinAmount,const float& MaxAmount);
};
