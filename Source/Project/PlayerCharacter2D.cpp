// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter2D.h"
 
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


APlayerCharacter2D::APlayerCharacter2D()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	
}

void APlayerCharacter2D::CalculateDirection(const float ActionValue)
{
	const FRotator CurrentDirection = Controller->GetControlRotation();
	
	if(ActionValue < 0.f)
	{
		if(CurrentDirection.Yaw != 180.f)
		{
			Controller->SetControlRotation(FRotator(CurrentDirection.Pitch,180.f,CurrentDirection.Roll));
		}
	}
	else if(ActionValue > 0.f)
	{
		if(CurrentDirection.Yaw != 0.f)
		{
			Controller->SetControlRotation(FRotator(CurrentDirection.Pitch,0.f,CurrentDirection.Roll));
		}
	}
}

//---------------------------------

void APlayerCharacter2D::Move(const FInputActionValue& InputActionValue)
{
	if(!Controller)
	{
		return;
	}
	
	const float ActionValue = InputActionValue.Get<float>();
	if(bIsAlive && bIsMovementAllowed)
	{
		const FVector Direction = FVector(1.f, 0.f, 0.f); 
		AddMovementInput(Direction, ActionValue);
		CalculateDirection(ActionValue);
	}
}

//---------------------------------

void APlayerCharacter2D::StartJump(const FInputActionValue& InputActionValue)
{
	if(bIsAlive && bIsMovementAllowed)
	{
		Jump();
	}
}

//---------------------------------

void APlayerCharacter2D::StopJump(const FInputActionValue& InputActionValue)
{
	StopJumping();
}

//---------------------------------

void APlayerCharacter2D::Attack(const FInputActionValue& InputActionValue)
{
	
}

//---------------------------------

void APlayerCharacter2D::BeginPlay()
{
	Super::BeginPlay();

	if(APlayerController* PC = static_cast<APlayerController*>(GetController()))
	{
		// Setup some bindings - we are currently using Enhanced Input and just using some input actions assigned in editor for simplicity
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Default, 0);
		}
	}
}

//---------------------------------

void APlayerCharacter2D::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

//---------------------------------

void APlayerCharacter2D::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInput = static_cast<UEnhancedInputComponent*>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacter2D::Move);
		
		EnhancedInput->BindAction(IA_Jump, ETriggerEvent::Started,this, &APlayerCharacter2D::StartJump);
		EnhancedInput->BindAction(IA_Jump, ETriggerEvent::Completed, this, &APlayerCharacter2D::StopJump);
		
		EnhancedInput->BindAction(IA_Attack, ETriggerEvent::Started, this, &APlayerCharacter2D::Attack);
	}
}

//---------------------------------
