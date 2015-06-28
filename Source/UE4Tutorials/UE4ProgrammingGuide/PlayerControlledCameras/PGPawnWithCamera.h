// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "PGPawnWithCamera.generated.h"


UCLASS()
class UE4TUTORIALS_API APGPawnWithCamera : public APawn
{
	GENERATED_BODY()

	FVector2D MovementInput, CameraInput;
	float ZoomFactor;
	bool bZoomingIn;


protected:

	UPROPERTY(EditAnywhere)
	USpringArmComponent* OurCameraSpringarm;

	UCameraComponent* OurCamera;

	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	void PitchCamera(float AxisValue);

	void YawCamera(float AxisValue);

	void ZoomIn();

	void ZoomOut();


public:

	APGPawnWithCamera();

	virtual void Tick( float DeltaSeconds ) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
};
