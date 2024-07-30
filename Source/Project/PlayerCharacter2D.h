#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "PaperZDAnimInstance.h"
#include "PaperZDCharacter.h"
#include "AnimSequences/PaperZDAnimSequence.h"
#include "PlayerCharacter2D.generated.h"

class UWallDetectorComponent;
class UInputAction;
class UInputMappingContext;
class UBoxComponent;
class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */

UENUM()
enum class EMoveState : uint8
{
	MOVE_Ground,
	MOVE_Air,
	MOVE_Wall
};

UCLASS()
class PROJECT_API APlayerCharacter2D : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter2D();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Skills, meta=(AllowPrivateAccess = "true"))
		float DashCooldownTime{2.f};
	
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

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> IA_Dash;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
		float DashForce{1000.f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Attack, meta=(AllowPrivateAccess = "true"))
		TObjectPtr<UPaperZDAnimSequence> AttackAnimationSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attack, meta=(AllowPrivateAccess = "true"))
		float AttackDmg{10.f};
	
	FZDOnAnimationOverrideEndSignature OnAttackOverrideEndDelegate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Attack, meta=(AllowPrivateAccess = "true"))
		TObjectPtr<UBoxComponent> AttackCollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UWallDetectorComponent> WallDetectorComponentForward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay, meta=(AllowPrivateAccess = "true"))
		float Health{30.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay, meta=(AllowPrivateAccess = "true"))
		float StunDuration{.3f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay|WallJump", meta=(AllowPrivateAccess = "true"))
		float WallHangDuration{2.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay|WallJump", meta=(AllowPrivateAccess = "true"))
		float WallJumpForce{500.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay|WallJump", meta=(AllowPrivateAccess = "true"))
		float WallHangDistance {24.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay", meta=(AllowPrivateAccess = "true"))
		float CustomGravityScale {2.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay|WallJump", meta=(AllowPrivateAccess = "true"))
		float WallJumpGravityScale {.5f};
	
	UPROPERTY(VisibleAnywhere, Category=Gameplay)
		FVector LastJumpLocation{};
	
	FTimerHandle DashTimerDelegateHandle;
	FTimerHandle StunTimerHandle;
	FTimerHandle WallJumpTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	EMoveState MovementState;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
		bool bIsAlive {true};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
		bool bIsMovementAllowed {true};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Attack)
		bool bCanAttack{true};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Attack)
		bool bCanDash{true};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gameplay|WallJump")
		bool bIsWallInRange{false};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Gameplay)
		bool bIsImmortal{false};

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category=Gameplay)
		bool bIsStunned{false};

	UFUNCTION(BlueprintCallable)
	void ToggleAttackCollisionBox(bool Enabled);

	//getters
	FORCEINLINE FVector GetLastJumpLocation() const {return LastJumpLocation;}

	FORCEINLINE EMoveState GetCurrentMoveState() const {return MovementState;}
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
								AController* EventInstigator, AActor* DamageCauser) override;

private:
	virtual void BeginPlay() override;

	/* Called when the Dash is ready to be used again */
	UFUNCTION()
	void OnDashTimerTimeOut();

	virtual void Landed(const FHitResult& Hit) override;
	
	void WallJump();
	
	/* Called when the PaperZD animation override ends.*/
	UFUNCTION()
	void OnAttackOverrideEndSequence(bool Completed);
	
	UFUNCTION()
	virtual void OnJumped_Implementation() override;

	void OnWallJumpTimerTimeOut();

	void OnStunTimerTimeOut();

	UFUNCTION()
	void OnAttackCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
										int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void SetDirectionFacing(const float ActionValue);
	
	void Move(const FInputActionValue& InputActionValue);

	void MoveCompleted(const FInputActionValue& InputActionValue);

	void HandleAirMovement(UCharacterMovementComponent* CMC);
	
	void StartJump(const FInputActionValue& InputActionValue);
	
	void StopJump(const FInputActionValue& InputActionValue);
	
	void Attack(const FInputActionValue& InputActionValue);
	
	void Dash(const FInputActionValue& InputActionValue);
	
	void ToggleGravity(const bool Enabled) const;

}; 
