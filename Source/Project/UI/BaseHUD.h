// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Project/Core/PlatformerGameInstance.h"
#include "BaseHUD.generated.h"

class UTextBlock;
class UProgressBar;
class UPlayerHUD;
class UPlatformerGameInstance;
/**
 * 
 */
UCLASS()
class PROJECT_API ABaseHUD : public AHUD
{
	GENERATED_BODY()

	ABaseHUD();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Gameplay|UI")
	TSubclassOf<UPlayerHUD> PlayerHudClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gameplay|Ui")
	TObjectPtr<UPlayerHUD> PlayerHudWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Gameplay|Core")
	TObjectPtr<UPlatformerGameInstance> GameInstance;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnHealthChanged(const int32& HP);

	UFUNCTION()
	void OnHealthDelayChanged(const int32& HPDelayed);

	UFUNCTION()
	void OnStaminaChanged(const int32& Stamina);

	UFUNCTION()
	void OnStaminaDelayChanged(const int32& StaminaDelayed);

	UFUNCTION()
	void OnDashBarChanged(const float& TimeLeft);
	
	UFUNCTION()
	void OnCreditsChanged(const int32& Credits);
	
public:
	void InitHud();
	
	float NormalizeValue(const float& CurrentValue, const float& MaxValue);

	void UpdateProgressBar(UProgressBar* ProgressBar, const float& Value, const float& MaxValue);
	
	void UpdateMinMaxText(UTextBlock* TextBlock, const FString& FormatString, const float& Min, const float& Max);

	void UpdateHealthText(const float& Min, const float& Max);
	
	void UpdateHPInstant(const float& Val);
	
	void UpdateHPDelayed(const float& Val);
	
	void UpdateStaminaText(const float& Min, const float& Max);
	
	void UpdateStaminaInstant(const float& Val);
	
	auto UpdateStaminaDelayed(const float& Val) -> void;

	void UpdateCredits(const int& Val);

	void UpdateDashBar(const float& Val);
	
	void ResetDashBar();
};
