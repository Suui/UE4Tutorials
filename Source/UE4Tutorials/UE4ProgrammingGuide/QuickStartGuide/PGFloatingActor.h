// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PGFloatingActor.generated.h"


UCLASS()
class UE4TUTORIALS_API APGFloatingActor : public AActor
{
	GENERATED_BODY()


public:

	float RunningTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FloatingActorProperties)
	float MovementMagnitude = 20.f;

	/* Minimal random magnitude of the movement applied on the X and Y axis */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FloatingActorProperties)
	float MinRandomScale = 0.6f;

	/* Maximum random magnitude of the movement applied on the X and Y axis */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FloatingActorProperties)
	float MaxRandomScale = 1.4f;

	APGFloatingActor();

	void Tick(float DeltaTime) override;
};
