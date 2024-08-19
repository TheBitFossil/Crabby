// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "WallDetectorComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_API UWallDetectorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWallDetectorComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsProcessing{false};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<AActor> WallActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bHasDetectedActor{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float OffsetDistance {20.f};

	void DetectWall();
	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<FHitResult> HitResults;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TraceDistance{32.f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float DetectedWallDistance{};

	void SetWallDetectorActive(const bool Value){ bIsProcessing = Value; }
	bool GetIsWallDetectorActive() const { return bIsProcessing; }

	bool HasDetectedActor() const {return bHasDetectedActor;}
	
	AActor* GetDetectedActor() const {return WallActor;}
};
