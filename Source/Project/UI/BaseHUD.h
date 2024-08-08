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
	void OnHealthChanged(const float& HP);

	UFUNCTION()
	void OnHealthDelayChanged(const float& HPDelayed);

	UFUNCTION()
	void OnStaminaChanged(const float& Stamina);

	UFUNCTION()
	void OnStaminaDelayChanged(const float& StaminaDelayed);

	UFUNCTION()
	void OnDashBarChanged(const float& TimeLeft);
	
	UFUNCTION()
	void OnCreditsChanged(const float& Credits);
	
public:
	void InitHud();
	
	float NormalizeValue(const float& CurrentValue, const float& MaxValue);

	void UpdateProgressBar(UProgressBar* ProgressBar, const float& Value, const float& MaxValue);
	
	void UpdateHPInstant(const float& Val);
	
	void UpdateHPDelayed(const float& Val);
	
	void UpdateStaminaInstant(const float& Val);
	
	auto UpdateStaminaDelayed(const float& Val) -> void;

	void UpdateCredits(const int& Val);

	void UpdateDashBar(const float& Val);
	
	void ResetDashBar();
};
