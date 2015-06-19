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
	float HeightScale = 20.f;

	APGFloatingActor();

	void Tick(float DeltaTime) override;
};
