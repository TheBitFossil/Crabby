#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "PaperZDAnimInstance.h"
#include "PaperZDCharacter.h"
#include "AnimSequences/PaperZDAnimSequence.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
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

private:
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
	
	/* Called when the PaperZD animation override ends.*/
	UFUNCTION()
	void OnAttackOverrideEndSequence(bool Completed);
	
	UFUNCTION()
	virtual void OnJumped_Implementation() override;
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
		TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
		TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
		TObjectPtr<UInputMappingContext> IMC_Default;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> IA_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Attack, meta=(AllowPrivateAccess = "true"))
		TObjectPtr<UPaperZDAnimSequence> AttackAnimationSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attack, meta=(AllowPrivateAccess = "true"))
		float AttackDmg{10.f};
	
	FZDOnAnimationOverrideEndSignature OnAttackOverrideEndDelegate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Attack, meta=(AllowPrivateAccess = "true"))
		TObjectPtr<UBoxComponent> AttackCollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay, meta=(AllowPrivateAccess = "true"))
	float Health{30.f};

	UFUNCTION()
	void OnAttackCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
										int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(VisibleAnywhere, Category=Gamneplay)
		FVector LastJumpLocation{};

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
		bool bIsAlive {true};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
		bool bIsMovementAllowed {true};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Attack)
		bool bCanAttack{true};
	
	UFUNCTION()
	FVector GetLastJumpLocation() const {return LastJumpLocation;}
	
	UFUNCTION(BlueprintCallable)
	void ToggleAttackCollisionBox(bool Enabled);
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
}; 
