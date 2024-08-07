#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "PaperZDAnimInstance.h"
#include "PaperZDCharacter.h"
#include "AnimSequences/PaperZDAnimSequence.h"
#include "Project/Core/PlatformerGameInstance.h"
#include "PlayerCharacter2D.generated.h"

class ABaseHUD;
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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
		TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
		TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
		TObjectPtr<UInputAction> IA_Attack;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
		TObjectPtr<UInputAction> IA_Dash;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
		TObjectPtr<UInputAction> IA_Equip_Slot_01;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
		TObjectPtr<UInputAction> IA_Bow_Draw;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Attack)
		TObjectPtr<UPaperZDAnimSequence> AttackAnimationSequence;
	
	FZDOnAnimationOverrideEndSignature OnAttackOverrideEndDelegate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Attack)
		TObjectPtr<UBoxComponent> AttackCollisionBox;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<UWallDetectorComponent> WallDetectorFront;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<UItemDetectorComponent> ItemDetectorComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UI)
		TObjectPtr<ABaseHUD> BaseHUD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gameplay|HP")
		int32 LastHealth{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gameplay|HP")
		int32 LastStamina{};
	
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

	void OnWallJumpTimerTimeOut();

	void OnStunTimerTimeOut();

	void OnHealthTickTimeout();

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
	
	void Move(const FInputActionValue& InputActionValue);

	void MoveCompleted(const FInputActionValue& InputActionValue);

	void HandleAirMovement(UCharacterMovementComponent* CMC);
	
	void StartJump(const FInputActionValue& InputActionValue);
	
	void StopJump(const FInputActionValue& InputActionValue);
	
	void Attack(const FInputActionValue& InputActionValue);
	
	void Dash(const FInputActionValue& InputActionValue);
		
	void ToggleGravity(const bool Enabled) const;

	void EquipSlot(const FInputActionValue& InputActionValue);
	
	void BowDraw(const FInputActionValue& InputActionValue);

	void InitBaseHud();
}; 