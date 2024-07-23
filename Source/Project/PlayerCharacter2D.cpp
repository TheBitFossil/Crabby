// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter2D.h"


APlayerCharacter2D::APlayerCharacter2D()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
}

//---------------------------------

void APlayerCharacter2D::BeginPlay()
{
	Super::BeginPlay();
}

//---------------------------------

void APlayerCharacter2D::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

//---------------------------------
