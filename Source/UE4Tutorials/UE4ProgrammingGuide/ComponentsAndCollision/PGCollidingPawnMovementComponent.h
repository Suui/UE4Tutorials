// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "PGCollidingPawnMovementComponent.generated.h"


UCLASS()
class UE4TUTORIALS_API UPGCollidingPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()


public:

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
