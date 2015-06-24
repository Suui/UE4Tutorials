// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PGCameraDirector.generated.h"


USTRUCT(BlueprintType)
struct UE4TUTORIALS_API FCameraProps
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeBeforeChangingToNextCamera = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SmoothBlendTime = 0.75f;

	FCameraProps() {}
};


UCLASS()
class UE4TUTORIALS_API APGCameraDirector : public AActor
{
	GENERATED_BODY()

	float TimeToNextCameraChange = 0.f;

	const float TIME_BETWEEN_CAMERA_CHANGES = 2.f;
	const float SMOOTH_BLEND_TIME = 0.75f;

	int Index = -1;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCameraProps> Cameras;

	APGCameraDirector();

	void Tick(float DeltaTime) override;
};
