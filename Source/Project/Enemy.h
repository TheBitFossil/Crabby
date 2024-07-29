// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimInstance.h"
#include "PaperZDCharacter.h"
#include "Components/SphereComponent.h"
#include "Enemy.generated.h"

class UBoxComponent;
class ALootDrop;
class APlayerCharacter2D;
class UTextRenderComponent;

UCLASS()
class PROJECT_API AEnemy : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TObjectPtr<USphereComponent> PlayerDetectorSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
		float DetectionRange{100.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
		float StoppingDistance{80.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
		bool bIsMovementAllowed {true};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<APlayerCharacter2D> PlayerTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Status)
		bool bIsAlive{true};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Status)
		float Health{50.f};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TObjectPtr<UTextRenderComponent> HealthDisplay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attack)
		float StunTime{0.f};

	FTimerHandle StunTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Attack)
		bool bIsStunned{false};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Attack)
		TObjectPtr<UPaperZDAnimSequence> AttackAnimationSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attack)
		bool bCanAttack{true};

	FTimerHandle AttackCooldownTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attack)
		float AttackCooldownTime{1.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attack)
		float AttackDmg{10.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attack)
		TObjectPtr<UBoxComponent> AttackCollisionBox;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
		TSubclassOf<ALootDrop> LootDrop;

	/* If Player is further than JumpThreshold vertically. Jump  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
		float JumpThreshold{10.f};

	/* Add Impulse after Jumping to help the AI traverse forward */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
		FVector JumpImpulse{100.f};

	FTimerHandle JumpCoolDownTimerHandle;

	FZDOnAnimationOverrideEndSignature OnAttackAnimationOverrideDelegate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
		float JumpTimer{5.f};

	void MoveHorizontalTo(const APlayerCharacter2D* Target);

	void UpdateDirection(const APlayerCharacter2D* Target);

	void JumpWithImpulse();
	
	UFUNCTION()
	void OnJumpCoolDownTimerTimeout();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UFUNCTION()
	void OnAttackCollisionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void OnAttackCoolDownTimerTimeOut();

	void Attack();

	UFUNCTION(BlueprintCallable)
	void ToggleAttackCollisionBox(bool Enabled);

	void OnAttackSequenceEnd(bool Completed);

	void UpdateHealth(int NewHealth);

	void Stun(float DurationInSeconds);
	void OnStunTimerTimeOut();
	
public:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
