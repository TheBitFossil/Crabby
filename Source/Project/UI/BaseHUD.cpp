// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUD.h"

#include "Project/UI/PlayerHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Project/Core/PlatformerGameInstance.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


ABaseHUD::ABaseHUD()
{
	
}

//---------------------------------

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();
	
	GameInstance = Cast<UPlatformerGameInstance>(GetGameInstance());
	if(GameInstance)
	{
		GameInstance->HealthChangedDelegate.AddDynamic(this, &ABaseHUD::OnHealthChanged);
		GameInstance->HealthDelayChangedDelegate.AddDynamic(this, &ABaseHUD::OnHealthDelayChanged);
		
		GameInstance->StaminaChangedDelegate.AddDynamic(this, &ABaseHUD::OnStaminaChanged);
		GameInstance->StaminaDelayChangedDelegate.AddDynamic(this, &ABaseHUD::OnStaminaDelayChanged);

		GameInstance->DashBarChangedDelegate.AddDynamic(this, &ABaseHUD::OnDashBarChanged);
		GameInstance->CreditsChangedDelegate.AddDynamic(this, &ABaseHUD::OnCreditsChanged);

		GameInstance->LevelChangedDelegate.AddDynamic(this, &ABaseHUD::OnLevelChanged);
		
		UE_LOG(LogTemp, Warning, TEXT("BaseHUD: Callbacks ready from Game Instance."))
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BaseHUD: Could not create callbacks from Game Instance."))
	}
	
	if(APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if(PlayerHudClass)
		{
			PlayerHudWidget = CreateWidget<UPlayerHUD>(PC, PlayerHudClass);
			if(PlayerHudWidget && GameInstance)
			{
				PlayerHudWidget->AddToPlayerScreen();
				InitHud();
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Please add the Player Hud Widget! Called from BaseHud.cpp."))
		}
	}
}

//---------------------------------

void ABaseHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

//---------------------------------

void ABaseHUD::OnHealthChanged(const float& HP)
{
	UpdateProgressBar(PlayerHudWidget->HealthProgressBarInstant, HP, GameInstance->GetMaxHealth());
	//UE_LOG(LogTemp, Warning, TEXT("OnHealthChanged(%f)"), HP);
}

//---------------------------------

void ABaseHUD::OnHealthDelayChanged(const float& HPDelayed)
{
	UpdateProgressBar(PlayerHudWidget->HealthProgressBarDelayed,HPDelayed, GameInstance->GetMaxHealth());

	//TODO:: Change the calls to the (HudWidget) inUse. to PlayerHudWidget->UpdateHealth(FText::FromString)
	// Goal: Each Widget takes care of how it handles its Visuals
	// Right now we can only work with this specific property [HealthTxt->]
	// Any changes to names or type would break compatibility 
	PlayerHudWidget->SetHealthTxt(HPDelayed, GameInstance->GetMaxHealth());
}

//---------------------------------

void ABaseHUD::OnStaminaChanged(const float& Stamina)
{
	UpdateProgressBar(PlayerHudWidget->StaminaProgressBarInstant,Stamina, GameInstance->GetMaxStamina());
}

//---------------------------------

void ABaseHUD::OnStaminaDelayChanged(const float& StaminaDelayed)
{
	UpdateProgressBar(PlayerHudWidget->StaminaProgressBarDelayed,StaminaDelayed, GameInstance->GetMaxStamina());

	FString Msg = FString::Printf(TEXT("SP:%0.0f/%0.0f"), StaminaDelayed, GameInstance->GetMaxStamina());
	PlayerHudWidget->StaminaTxt->SetText(FText::FromString(Msg));
}

//---------------------------------

void ABaseHUD::OnDashBarChanged(const float& TimeLeft)
{
	UpdateProgressBar(PlayerHudWidget->DashProgressBar,TimeLeft,	GameInstance->GetMaxDashCoolDown());
}

//---------------------------------

void ABaseHUD::OnCreditsChanged(const float& Credits)
{
	UpdateCreditsTxt(Credits);
}

//---------------------------------

void ABaseHUD::InitHud()
{
	PlayerHudWidget->SetHealthTxt(GameInstance->GetHealth(), GameInstance->GetMaxHealth());
	UpdateHPInstant(GameInstance->GetHealth());
	UpdateHPDelayed(GameInstance->GetHealthDelayed());

	PlayerHudWidget->SetStaminaTxt(GameInstance->GetStamina(), GameInstance->GetMaxStamina());
	UpdateStaminaInstant(GameInstance->GetStamina());
	UpdateStaminaDelayed(GameInstance->GetStaminaDelayed());

	UpdateCreditsTxt(GameInstance->GetCredits());
	UpdateDashBar(GameInstance->GetDashCoolDown());
	UpdateLevelTxt(GameInstance->GetCurrentLevel());
}

//---------------------------------
/*
 * Used for ProgressBars to fit Values bigger than 1
 */
float ABaseHUD::NormalizeValue(const float& CurrentValue, const float& MaxValue)
{
	const float NormalizedValue = FMath::Clamp(CurrentValue / MaxValue, 0.f, 1.f);
	
	//UE_LOG(LogTemp, Log, TEXT("Normalized Value: %f (Current: %f, Max: %f)"), NormalizedValue, CurrentValue, MaxValue);
	return NormalizedValue;
}

//---------------------------------

void ABaseHUD::UpdateProgressBar(UProgressBar* ProgressBar, const float& Value, const float& MaxValue)
{
	if(ProgressBar)
	{
		const float Percent = NormalizeValue(Value, MaxValue);
		ProgressBar->SetPercent(Percent);
	}
}

//---------------------------------

void ABaseHUD::UpdateHPInstant(const float& Val)
{
	UpdateProgressBar(PlayerHudWidget->HealthProgressBarInstant, Val, GameInstance->GetMaxHealth());
}

//---------------------------------

void ABaseHUD::UpdateHPDelayed(const float& Val)
{
	UpdateProgressBar(PlayerHudWidget->HealthProgressBarDelayed, Val, GameInstance->GetHealth());
}

//---------------------------------

void ABaseHUD::UpdateStaminaInstant(const float& Val)
{
	UpdateProgressBar(PlayerHudWidget->StaminaProgressBarInstant,GameInstance->GetStamina(),GameInstance->GetMaxStamina());
}

//---------------------------------

void ABaseHUD::UpdateStaminaDelayed(const float& Val)
{
	UpdateProgressBar(PlayerHudWidget->StaminaProgressBarDelayed,Val, GameInstance->GetMaxStamina());
}

//---------------------------------

void ABaseHUD::UpdateCreditsTxt(const float& Val)
{
	PlayerHudWidget->SetCreditsTxt(Val);
}

//---------------------------------

void ABaseHUD::UpdateDashBar(const float& Val)
{
	UpdateProgressBar(PlayerHudWidget->DashProgressBar,Val, GameInstance->GetMaxDashCoolDown());
}

//---------------------------------

void ABaseHUD::UpdateLevelTxt(const float& Val)
{
	PlayerHudWidget->SetLevelTxt(Val);
}

//---------------------------------

void ABaseHUD::ResetDashBar()
{
	UpdateProgressBar(PlayerHudWidget->DashProgressBar,0.f, GameInstance->GetMaxDashCoolDown());
}

//---------------------------------

void ABaseHUD::OnLevelChanged(const float& CurrentLevel)
{
	UpdateLevelTxt(CurrentLevel);
	
}