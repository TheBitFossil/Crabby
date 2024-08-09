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
	TObjectPtr<UInputAction> IA_Punch;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Kick;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Weapon;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Block;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|Inventory")
	TObjectPtr<UInputAction> IA_Grab;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Aim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|Inventory")
	TObjectPtr<UInputAction> IA_Equip_Bow;
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

	void Move(const FInputActionValue& InputActionValue);
	void MoveCompleted(const FInputActionValue& InputActionValue);
	void Run(const FInputActionValue& InputActionValue);
	void Dash(const FInputActionValue& InputActionValue);
	void Jump(const FInputActionValue& InputActionValue);
	void StopJump(const FInputActionValue& InputActionValue);
	void Crouch(const FInputActionValue& InputActionValue);
	void Punch(const FInputActionValue& InputActionValue);
	void Kick(const FInputActionValue& InputActionValue);
	void Weapon(const FInputActionValue& InputActionValue);
	void Block(const FInputActionValue& InputActionValue);
	void Grab(const FInputActionValue& InputActionValue);
	void EquipBow(const FInputActionValue& InputActionValue);
	void Aim(const FInputActionValue& InputActionValue);
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
