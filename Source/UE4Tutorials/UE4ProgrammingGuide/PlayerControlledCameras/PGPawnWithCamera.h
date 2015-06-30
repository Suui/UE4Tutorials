// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "PGPawnWithCamera.generated.h"


UCLASS()
class UE4TUTORIALS_API APGPawnWithCamera : public APawn
{
	GENERATED_BODY()

	FVector2D MovementInput, CameraInput;
	FVector CameraMotion;

	float ZoomFactor;
	bool bZoomingIn, bIsRunning;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PawnWithCamera Properties")
	float WalkingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PawnWithCamera Properties")
	float RunningSpeed;

	UPROPERTY(VisibleAnywhere, Category = "PawnWithCamera Properties")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PawnWithCamera Properties")
	float CameraMotionFactor;


protected:

	UPROPERTY(VisibleAnywhere, Category = "PawnWithCamera Properties")
	USpringArmComponent* OurCameraSpringarm;

	UPROPERTY(VisibleAnywhere, Category = "PawnWithCamera Properties")
	UCameraComponent* OurCamera;

	UPROPERTY(VisibleAnywhere, Category = "PawnWithCamera Properties")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PawnWithCamera Properties")
	UCurveVector* CameraMotionCurve;

	void CalculateMovementSpeed();

	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	void PitchCamera(float AxisValue);

	void YawCamera(float AxisValue);

	void ZoomIn();

	void ZoomOut();

	void Run();

	void StopRunning();


public:

	APGPawnWithCamera();

	void PostInitProperties() override;

	virtual void Tick( float DeltaSeconds ) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
