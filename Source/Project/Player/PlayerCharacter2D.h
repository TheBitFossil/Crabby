#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "PaperZDAnimInstance.h"
#include "PaperZDCharacter.h"
#include "AnimSequences/PaperZDAnimSequence.h"
#include "Project/Core/PlatformerGameInstance.h"
#include "Project/DataAssets/AnimationDataAsset.h"
#include "PlayerCharacter2D.generated.h"

class UAnimationComboComponent;
class UAnimationDataAsset;
class UInputActionsComponent;
class UItemDetectorComponent;
class UPlatformerGameInstance;
class UWallDetectorComponent;
class UInputAction;
class UInputMappingContext;
class UBoxComponent;
class USpringArmComponent;
class UCameraComponent;
class UPlayerHUD;
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

UENUM()
enum class EAnimationState : int32
{
	Walking,
	Dashing,
	Running,
	Punch,
	Kick,
	Block,
	Grab,
	Sword,
	Bow,
	Aim,
	Crouching,
	GettingHit,
	Rolling,
};

UCLASS()
class PROJECT_API APlayerCharacter2D : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter2D();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
		TObjectPtr<UInputMappingContext> IMC_Default;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Attack)
		TObjectPtr<UPaperZDAnimSequence> AttackAnimationSequence;
	
	FZDOnAnimationOverrideEndSignature OnAttackOverrideEndDelegate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Attack)
		TObjectPtr<UBoxComponent> AttackCollisionBox;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<UWallDetectorComponent> WallDetectorFront;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
		TObjectPtr<UItemDetectorComponent> ItemDetectorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
		TObjectPtr<UInputActionsComponent> InputActionsComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
		TObjectPtr<UAnimationDataAsset> AttackAnimationDataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
		TObjectPtr<UAnimationComboComponent> AnimationComboComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
		TObjectPtr<UCharacterMovementComponent> CMC;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gameplay|HP")
		int32 DamageTaken {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay|Attack")
		float AttackDmg{10.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay|Ui")
		float HealthTickRate{1.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay|Ui")
		int32 HealthRemovePerTick{20};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay|Ui")
		float StaminaTickRate{1.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay|Ui")
		int32 StaminaRemovePerTick{20};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay|Movement")
		float StunDuration{.3f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Gameplay|Movement")
		float DashForce{1000.f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Gameplay|Ui")
		float DashCoolDownTickRate{.2f};		// Visual Update Rate

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Gameplay|Ui")
		float DashCoolDownTickAmount{0.1f};		// Amount added per Tick 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gameplay|Movement")
		float CurrentDashTimer{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay|Movement")
		int32 StaminaRegenAmount{10};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay|Movement")
		float StaminaRegenTickRate{1.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay|Movement")
		int32 StaminaCostDash{25};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay|WallJump")
		float WallHangDuration{2.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay|WallJump")
		float WallJumpForce{500.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay|WallJump")
		float WallHangDistance {24.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay|Movement", meta=(ClampMin = "0.1", ClampMax = "4"))
		float CustomGravityScale {2.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay|WallJump", meta=(ClampMin = "0.1", ClampMax = "4"))
		float WallJumpGravityScale {.35f};
	
	UPROPERTY(VisibleAnywhere, Category="Gameplay|Movement")
		FVector LastJumpLocation{};

	FTimerHandle DashTimerDelegate;
	FTimerHandle StunTimerDelegate;
	FTimerHandle StaminaRegenDelegate;
	FTimerHandle WallJumpTimerDelegate;

	FTimerHandle HealthTickDelegate;
	FTimerHandle StaminaTickDelegate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gameplay|Movement")
		EMoveState MovementState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gameplay|Movement")
		EAnimationState AnimationState;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Gameplay|Core")
		TObjectPtr<UPlatformerGameInstance> GameInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Inventory)
		bool bEquippedSlot01 {false};

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

	virtual void Landed(const FHitResult& Hit) override;
	
	void WallJump();
	
	/* Called when the PaperZD animation override ends.*/
	UFUNCTION()
	void OnAttackOverrideEndSequence(bool Completed);
	
	UFUNCTION()
	virtual void OnJumped_Implementation() override;

	void UpdateAttributeTick(float& Last, const float& Current, const float& TotalAmount, const float& RemovalPerTick,
	                         FTimerHandle& TimerHandle, const FString& AttributeName,
	                         TFunction<void(float)> UpdateRefFunction, float TickRate);

	void OnWallJumpTimerTimeOut();

	void OnStunTimerTimeOut();

	void OnHealthTickTimeOut();

	void OnStaminaTickTimeOut();
	
	/* Called when the Dash is ready to be used again */
	void OnDashTimerTimeOut();
	
	void OnStaminaRegenTimeOut();
	
	UFUNCTION()
	void OnAttackCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
										int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void SetDirectionFacing(const float ActionValue);

public:
	void Move(const FInputActionValue& InputActionValue);
	void MoveCompleted(const FInputActionValue& InputActionValue);
	void Run(const FInputActionValue& InputActionValue);
	void Dash(const FInputActionValue& InputActionValue);
	void StartJump(const FInputActionValue& InputActionValue);
	void StopJump(const FInputActionValue& InputActionValue);
	void Crouching(const FInputActionValue& InputActionValue);
	void Weapon(const FInputActionValue& InputActionValue);
	void Punch(const FInputActionValue& InputActionValue);
	void Kick(const FInputActionValue& InputActionValue);
	void Block(const FInputActionValue& InputActionValue);
	void Grab(const FInputActionValue& InputActionValue);
	void EquipBow(const FInputActionValue& InputActionValue);
	void Aim(const FInputActionValue& InputActionValue);

private:
	void HandleAirMovement(UCharacterMovementComponent* CharacterMovement);
	void ChangeAnimationState(const EAnimationState& Dashing);
	void ToggleGravity(const bool Enabled) const;
}; 