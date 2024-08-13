// Fill out your copyright notice in the Description page of Project Settings.


#include "InputActionsComponent.h"

#include "EnhancedInputComponent.h"
#include "Project/Player/PlayerCharacter2D.h"

UInputActionsComponent::UInputActionsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

//---------------------------------

void UInputActionsComponent::BeginPlay()
{
	Super::BeginPlay();

	if((PlayerCharacter2D = Cast<APlayerCharacter2D>(GetOwner())))
	{
		if(UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerCharacter2D->InputComponent))
		{
			BindInputActions(EnhancedInput);
		}
	}
}

//---------------------------------

void UInputActionsComponent::BindInputActions(UEnhancedInputComponent* EnhancedInputComponent)
{
	if (InputConfig.IA_Move)
	{
		EnhancedInputComponent->BindAction(InputConfig.IA_Move, ETriggerEvent::Triggered, this, &UInputActionsComponent::Move);
		EnhancedInputComponent->BindAction(InputConfig.IA_Move, ETriggerEvent::Canceled, this, &UInputActionsComponent::MoveCompleted);
	}

	if (InputConfig.IA_Run)
	{
		EnhancedInputComponent->BindAction(InputConfig.IA_Run, ETriggerEvent::Triggered, this, &UInputActionsComponent::Run);
		EnhancedInputComponent->BindAction(InputConfig.IA_Run, ETriggerEvent::Canceled, this, &UInputActionsComponent::Run);
	}

	if (InputConfig.IA_Dash)
	{
		EnhancedInputComponent->BindAction(InputConfig.IA_Dash, ETriggerEvent::Triggered, this, &UInputActionsComponent::Dash);
	}

	if (InputConfig.IA_Jump)
	{
		EnhancedInputComponent->BindAction(InputConfig.IA_Jump, ETriggerEvent::Triggered, this, &UInputActionsComponent::Jump);
		EnhancedInputComponent->BindAction(InputConfig.IA_Jump, ETriggerEvent::Canceled, this, &UInputActionsComponent::StopJump);
	}

	if (InputConfig.IA_Crouch)
	{
		EnhancedInputComponent->BindAction(InputConfig.IA_Crouch, ETriggerEvent::Triggered, this, &UInputActionsComponent::Crouch);
		EnhancedInputComponent->BindAction(InputConfig.IA_Crouch, ETriggerEvent::Canceled, this, &UInputActionsComponent::Crouch);
	}
	
	if (InputConfig.IA_Kick)
	{
		EnhancedInputComponent->BindAction(InputConfig.IA_Kick, ETriggerEvent::Triggered, this, &UInputActionsComponent::Kick);
	}

	if (InputConfig.IA_Block)
	{
		EnhancedInputComponent->BindAction(InputConfig.IA_Block, ETriggerEvent::Triggered, this, &UInputActionsComponent::Block);
		EnhancedInputComponent->BindAction(InputConfig.IA_Block, ETriggerEvent::Canceled, this, &UInputActionsComponent::Block);
	}
	
	if (InputConfig.IA_Punch)
	{
		EnhancedInputComponent->BindAction(InputConfig.IA_Punch, ETriggerEvent::Triggered, this, &UInputActionsComponent::Punch);
	}

	if (InputConfig.IA_Weapon)
	{
		EnhancedInputComponent->BindAction(InputConfig.IA_Weapon, ETriggerEvent::Triggered, this, &UInputActionsComponent::Weapon);
	}
	
	if (InputConfig.IA_Grab)
	{
		EnhancedInputComponent->BindAction(InputConfig.IA_Grab, ETriggerEvent::Triggered, this, &UInputActionsComponent::Grab);
	}

	if (InputConfig.IA_Equip_Bow)
	{
		EnhancedInputComponent->BindAction(InputConfig.IA_Equip_Bow, ETriggerEvent::Triggered, this, &UInputActionsComponent::EquipBow);
	}

	if (InputConfig.IA_Aim)
	{
		EnhancedInputComponent->BindAction(InputConfig.IA_Aim, ETriggerEvent::Triggered, this, &UInputActionsComponent::Aim);
		EnhancedInputComponent->BindAction(InputConfig.IA_Aim, ETriggerEvent::Canceled, this, &UInputActionsComponent::Aim);
	}
}


//---------------------------------

void UInputActionsComponent::Move(const FInputActionValue& InputActionValue)
{
	if(PlayerCharacter2D)
	{
		PlayerCharacter2D->Move(InputActionValue);
	}
}
//---------------------------------

void UInputActionsComponent::MoveCompleted(const FInputActionValue& InputActionValue)
{
	if(PlayerCharacter2D)
	{
		PlayerCharacter2D->MoveCompleted(InputActionValue);
	}
}

//---------------------------------

void UInputActionsComponent::Run(const FInputActionValue& InputActionValue)
{
	if(PlayerCharacter2D)
	{
		PlayerCharacter2D->Run(InputActionValue);
	}
}

//---------------------------------

void UInputActionsComponent::Dash(const FInputActionValue& InputActionValue)
{
	if(PlayerCharacter2D)
	{
		PlayerCharacter2D->Dash(InputActionValue);
	}
}


//---------------------------------

void UInputActionsComponent::Jump(const FInputActionValue& InputActionValue)
{
	if(PlayerCharacter2D)
	{
		PlayerCharacter2D->StartJump(InputActionValue);
	}
}

//---------------------------------

void UInputActionsComponent::StopJump(const FInputActionValue& InputActionValue)
{
	if(PlayerCharacter2D)
	{
		PlayerCharacter2D->StopJump(InputActionValue);
	}
}

//---------------------------------

void UInputActionsComponent::Crouch(const FInputActionValue& InputActionValue)
{
	if(PlayerCharacter2D)
	{
		PlayerCharacter2D->Crouching(InputActionValue);
	}
}

//---------------------------------

void UInputActionsComponent::Weapon(const FInputActionValue& InputActionValue)
{
	if(PlayerCharacter2D)
	{
		PlayerCharacter2D->Weapon(InputActionValue);
	}
}


//---------------------------------

void UInputActionsComponent::Punch(const FInputActionValue& InputActionValue)
{
	if(PlayerCharacter2D)
	{
		PlayerCharacter2D->Punch(InputActionValue);
	}
}

//---------------------------------

void UInputActionsComponent::Kick(const FInputActionValue& InputActionValue)
{
	if(PlayerCharacter2D)
	{
		PlayerCharacter2D->Kick(InputActionValue);
	}
}

//---------------------------------

void UInputActionsComponent::Block(const FInputActionValue& InputActionValue)
{
	if(PlayerCharacter2D)
	{
		PlayerCharacter2D->Block(InputActionValue);
	}
}

//---------------------------------

void UInputActionsComponent::Grab(const FInputActionValue& InputActionValue)
{
	if(PlayerCharacter2D)
	{
		PlayerCharacter2D->Grab(InputActionValue);
	}
}

//---------------------------------

void UInputActionsComponent::EquipBow(const FInputActionValue& InputActionValue)
{
	if(PlayerCharacter2D)
	{
		PlayerCharacter2D->EquipBow(InputActionValue);
	}
}

//---------------------------------

void UInputActionsComponent::Aim(const FInputActionValue& InputActionValue)
{
	if(PlayerCharacter2D)
	{
		PlayerCharacter2D->Aim(InputActionValue);
	}
}

//---------------------------------

// Called every frame
void UInputActionsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

