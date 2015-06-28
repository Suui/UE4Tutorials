// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "PGPawnWithCamera.generated.h"


UCLASS()
class UE4TUTORIALS_API APGPawnWithCamera : public APawn
{
	GENERATED_BODY()


protected:

	UPROPERTY(EditAnywhere)
	USpringArmComponent* OurCameraSpringarm;

	UCameraComponent* OurCamera;


public:

	APGPawnWithCamera();

	virtual void Tick( float DeltaSeconds ) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
};
