#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacter2D.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API APlayerCharacter2D : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter2D();

protected:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	
}; 
