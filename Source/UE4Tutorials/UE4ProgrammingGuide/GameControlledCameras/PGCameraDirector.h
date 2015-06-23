// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PGCameraDirector.generated.h"


UCLASS()
class UE4TUTORIALS_API APGCameraDirector : public AActor
{
	GENERATED_BODY()

	float TimeToNextCameraChange;

	const float TIME_BETWEEN_CAMERA_CHANGES = 2.f;
	const float SMOOTH_BLEND_TIME = 0.75f;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* CameraOne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* CameraTwo;

	APGCameraDirector();

	void Tick(float DeltaTime) override;
};
