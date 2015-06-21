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

	/* The magnitude for the movement in the X, Y, Z axis (How large the Sine movement is) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FloatingActorProperties)
	FVector MovementMagnitude = FVector(20.f, 20.f, 20.f);

	/* The scale for the movement in the X, Y, Z axis (How fast the Sine movement is) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FloatingActorProperties)
	FVector MovementScale = FVector(2.2f, 1.4f, 1.f);

	APGFloatingActor();

	void Tick(float DeltaTime) override;
};
