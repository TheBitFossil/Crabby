// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Components/ActorComponent.h"
#include "Project/Player/PlayerCharacter2D.h"
#include "InputActionsComponent.generated.h"

class UInputAction;
class UEnhancedInputComponent;

USTRUCT(BlueprintType)
struct FInputConfig
{
	GENERATED_BODY()
	FInputConfig();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Run;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Dash;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Jump;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Crouch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|Inventory")
	TObjectPtr<UInputAction> IA_Equip_Melee;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|Inventory")
	TObjectPtr<UInputAction> IA_Equip_Sword;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|Inventory")
	TObjectPtr<UInputAction> IA_Equip_Bow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Block;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Aim;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UInputActionsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInputActionsComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input)
	FInputConfig InputConfig;

	
	void BindInputActions(UEnhancedInputComponent* EnhancedInputComponent);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerCharacter2D> PlayerCharacter2D = nullptr;

	virtual void BeginPlay() override;
	
	void Attack(const FInputActionValue& InputActionValue);
	void Crouch(const FInputActionValue& FInputActionValue);
	void Jump(const FInputActionValue& FInputActionValue);
	void StopJump(const FInputActionValue& InputActionValue);
	void Dash(const FInputActionValue& FInputActionValue);
	void Run(const FInputActionValue& FInputActionValue);
	void Move(const FInputActionValue& FInputActionValue);
	void Block(const FInputActionValue& FInputActionValue);
	void EquipMelee(const FInputActionValue& FInputActionValue);
	void EquipSword(const FInputActionValue& FInputActionValue);
	void EquipBow(const FInputActionValue& FInputActionValue);
	void Aim(const FInputActionValue& FInputActionValue);
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
		
};
