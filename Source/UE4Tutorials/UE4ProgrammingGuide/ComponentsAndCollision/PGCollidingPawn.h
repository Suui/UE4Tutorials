// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "PGCollidingPawn.generated.h"

class UPGCollidingPawnMovementComponent;


UCLASS()
class UE4TUTORIALS_API APGCollidingPawn : public APawn
{
	GENERATED_BODY()


protected:

	UParticleSystemComponent* OurParticleSystem;

	UPGCollidingPawnMovementComponent* OurMovementComponent;

	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	void Turn(float AxisValue);

	void ToggleParticle();


public:

	APGCollidingPawn();

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPawnMovementComponent* GetMovementComponent() const override;
};
