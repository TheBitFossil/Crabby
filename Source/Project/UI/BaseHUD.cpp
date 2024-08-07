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

void ABaseHUD::OnHealthChanged(const int32& HP)
{
	UpdateProgressBar(
		PlayerHudWidget->HealthProgressBarInstant,
		HP,
		GameInstance->PlayerData.MaxHP
	);

	UpdateHealthText(HP, GameInstance->PlayerData.MaxHP);
}

//---------------------------------

void ABaseHUD::OnHealthDelayChanged(const int32& HPDelayed)
{
	UpdateProgressBar(
		PlayerHudWidget->HealthProgressBarDelayed,
		HPDelayed,
		GameInstance->PlayerData.MaxHP
	);

	UpdateHealthText(HPDelayed, GameInstance->PlayerData.MaxHP);
}

//---------------------------------

void ABaseHUD::OnStaminaChanged(const int32& Stamina)
{
	UpdateProgressBar(
		PlayerHudWidget->StaminaProgressBarInstant,
		Stamina,
		GameInstance->PlayerData.MaxSP
	);

	UpdateStaminaText(Stamina, GameInstance->PlayerData.MaxSP);
}

//---------------------------------

void ABaseHUD::OnStaminaDelayChanged(const int32& StaminaDelayed)
{
	UpdateProgressBar(
		PlayerHudWidget->StaminaProgressBarDelayed,
		StaminaDelayed,
		GameInstance->PlayerData.MaxSP
	);

	UpdateStaminaText(StaminaDelayed, GameInstance->PlayerData.MaxSP);
}

//---------------------------------

void ABaseHUD::OnDashBarChanged(const float& TimeLeft)
{
	UpdateProgressBar(
		PlayerHudWidget->DashProgressBar,
		TimeLeft,
		GameInstance->PlayerData.MaxDashCoolDown
	);
}

//---------------------------------

void ABaseHUD::OnCreditsChanged(const int32& Credits)
{
	
}

//---------------------------------

void ABaseHUD::InitHud()
{
	PlayerHudWidget->SetLevelTxt(909);

	// Log the initial values
	UE_LOG(LogTemp, Log, TEXT("Initializing HUD with HP: %f / %f"), GameInstance->PlayerData.HP, GameInstance->PlayerData.MaxHP);
	
	UpdateHealthText(GameInstance->PlayerData.HP, GameInstance->PlayerData.MaxHP);
	UpdateHPInstant(GameInstance->PlayerData.HP);
	UpdateHPDelayed(GameInstance->PlayerData.HP);
	
	UpdateStaminaText(GameInstance->PlayerData.SP, GameInstance->PlayerData.MaxSP);
	UpdateStaminaInstant(GameInstance->PlayerData.SP);
	UpdateStaminaDelayed(GameInstance->PlayerData.SP);

	UpdateCredits(GameInstance->PlayerData.Credits);
	UpdateDashBar(GameInstance->PlayerData.DashCoolDown);
}

//---------------------------------
/*
 * Used for ProgressBars to fit Values bigger than 1
 */
float ABaseHUD::NormalizeValue(const float& CurrentValue, const float& MaxValue)
{
	float NormalizedValue = FMath::Clamp(CurrentValue / MaxValue, 0.f, 1.f);
	UE_LOG(LogTemp, Log, TEXT("Normalized Value: %f (Current: %f, Max: %f)"), NormalizedValue, CurrentValue, MaxValue);
	return NormalizedValue;
}

//---------------------------------

void ABaseHUD::UpdateProgressBar(UProgressBar* ProgressBar, const float& Value, const float& MaxValue)
{
	const float Percent = NormalizeValue(Value, MaxValue);
	if(ProgressBar)
	{
		ProgressBar->SetPercent(Percent);
	}
}

//---------------------------------

void ABaseHUD::UpdateMinMaxText(UTextBlock* TextBlock, const FString& FormatString, const float& Min, const float& Max)
{
	if(TextBlock)
	{
		const FString Msg = FString::Printf(*FormatString, Min, Max);
		TextBlock->SetText(FText::FromString(Msg));
	}
}

//---------------------------------

void ABaseHUD::UpdateHealthText(const float& Min, const float& Max)
{
	UpdateMinMaxText(
		PlayerHudWidget->HealthTxt,
		TEXT("HP: %d / %d"),
		Min,
		Max
	);
}

//---------------------------------

void ABaseHUD::UpdateHPInstant(const float& Val)
{
	UpdateProgressBar(PlayerHudWidget->HealthProgressBarInstant, Val, GameInstance->PlayerData.MaxHP);
}

//---------------------------------

void ABaseHUD::UpdateHPDelayed(const float& Val)
{
	UpdateProgressBar(PlayerHudWidget->HealthProgressBarDelayed, Val, GameInstance->PlayerData.MaxHP);

	UpdateHealthText(Val, GameInstance->PlayerData.MaxHP);
}

//---------------------------------

void ABaseHUD::UpdateStaminaText(const float& Min, const float& Max)
{
	UpdateMinMaxText(
		PlayerHudWidget->StaminaTxt,
		TEXT("SP: %d / %d"),
		Min,
		Max
	);
}

//---------------------------------

void ABaseHUD::UpdateStaminaInstant(const float& Val)
{
	UpdateProgressBar(PlayerHudWidget->StaminaProgressBarInstant,
						GameInstance->PlayerData.SP,GameInstance->PlayerData.MaxSP);
}

//---------------------------------

void ABaseHUD::UpdateStaminaDelayed(const float& Val)
{
	UpdateProgressBar(PlayerHudWidget->StaminaProgressBarDelayed,Val, GameInstance->PlayerData.MaxSP);
	
	UpdateStaminaText(Val, GameInstance->PlayerData.MaxSP);
}

//---------------------------------

void ABaseHUD::UpdateCredits(const int& Val)
{
	PlayerHudWidget->SetCreditsTxt(Val);
}

//---------------------------------

void ABaseHUD::UpdateDashBar(const float& Val)
{
	UpdateProgressBar(PlayerHudWidget->DashProgressBar,Val, GameInstance->PlayerData.MaxDashCoolDown);
}

//---------------------------------

void ABaseHUD::ResetDashBar()
{
	UpdateProgressBar(PlayerHudWidget->DashProgressBar,0.f, GameInstance->PlayerData.MaxDashCoolDown);
}

