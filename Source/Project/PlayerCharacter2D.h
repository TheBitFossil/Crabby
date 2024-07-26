#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "PaperZDAnimInstance.h"
#include "PaperZDCharacter.h"
#include "AnimSequences/PaperZDAnimSequence.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacter2D.generated.h"

class UInputAction;
class UInputMappingContext;
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
	UFUNCTION()
	void CalculateDirection(const float ActionValue);
	
	UFUNCTION()
	void Move(const FInputActionValue& InputActionValue);

	UFUNCTION()
	void StartJump(const FInputActionValue& InputActionValue);

	UFUNCTION()
	void StopJump(const FInputActionValue& InputActionValue);

	UFUNCTION()
	void Attack(const FInputActionValue& InputActionValue);

	UFUNCTION()
	virtual void OnJumped_Implementation() override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input)
	TObjectPtr<UInputMappingContext> IMC_Default;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input)
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input)
	TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input)
	TObjectPtr<UInputAction> IA_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Attack)
	TObjectPtr<UPaperZDAnimSequence> AttackAnimationSequence;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Attack)
	bool bCanAttack{true};

	FZDOnAnimationOverrideEndSignature OnAttackOverrideEndDelegate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	bool bIsMovementAllowed {true};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	bool bIsAlive {true};

	UFUNCTION()
	FVector GetLastJumpLocation() const {return LastJumpLocation;}

	/* Called when the PaperZD animation override ends.*/
	UFUNCTION()
	void OnAttackOverrideEndSequence(bool Completed);
	
private:
	UPROPERTY(VisibleAnywhere, Category=Gamneplay)
	FVector LastJumpLocation{};
}; 
