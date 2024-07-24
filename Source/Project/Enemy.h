// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Components/SphereComponent.h"
#include "Enemy.generated.h"

class ALootDrop;
class APlayerCharacter2D;

UCLASS()
class PROJECT_API AEnemy : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> PlayerDetectorSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DetectionRange{100.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StoppingDistance{10.f};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<APlayerCharacter2D> PlayerTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAlive{true};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health{100.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	TSubclassOf<ALootDrop> LootDrop;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
