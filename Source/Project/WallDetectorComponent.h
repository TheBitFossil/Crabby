// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WallDetectorComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_API UWallDetectorComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UWallDetectorComponent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess ="true"))
		bool bIsWallInRange{false};
	
	bool IsWallInRange(const float& WallHangRange, const FHitResult& HitResult);
	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FHitResult> HitResults;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TraceDistance{100.f};
	
	bool IsDetectingWall(const float& WallHangRange, const AActor* IgnoredActor);
	
	UFUNCTION()
	FORCEINLINE bool CanWallHang() const {return bIsWallInRange;}
};
