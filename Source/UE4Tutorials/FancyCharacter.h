// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "FancyCharacter.generated.h"

UCLASS()
class UE4TUTORIALS_API AFancyCharacter : public ACharacter
{
	GENERATED_BODY()

	const float YAW_PITCH_MULTIPLIER = 200.0f;

public:
	// Sets default values for this character's properties
	AFancyCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void MoveForward(float Amount);

	void Strafe(float Amount);

	void Yaw(float Amount);

	void Pitch(float Amount);
};
