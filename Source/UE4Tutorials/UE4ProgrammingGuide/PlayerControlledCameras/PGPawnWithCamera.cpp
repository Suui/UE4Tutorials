// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "PGPawnWithCamera.h"



APGPawnWithCamera::APGPawnWithCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root Component");

	OurCameraSpringarm = CreateDefaultSubobject<USpringArmComponent>("Camera Spring Arm");
	OurCameraSpringarm->AttachTo(RootComponent);
	OurCameraSpringarm->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 50.f), FRotator(-60.f, 0.f, 0.f));
	OurCameraSpringarm->TargetArmLength = 400.f;
	OurCameraSpringarm->bEnableCameraLag = true;
	OurCameraSpringarm->CameraLagSpeed = 3.f;

	OurCamera = CreateDefaultSubobject<UCameraComponent>("Game Camera");
	OurCamera->AttachTo(OurCameraSpringarm, USpringArmComponent::SocketName);
}


/*----------------------------------------------------------------
- Protected functions -
----------------------------------------------------------------*/

void APGPawnWithCamera::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.f, 1.f);
}


void APGPawnWithCamera::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.f, 1.f);
}


void APGPawnWithCamera::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}


void APGPawnWithCamera::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}


void APGPawnWithCamera::ZoomIn()
{
	bZoomingIn = true;
}


void APGPawnWithCamera::ZoomOut()
{
	bZoomingIn = false;
}


void APGPawnWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bZoomingIn)
		ZoomFactor += DeltaTime / 0.5f;
	else
		ZoomFactor -= DeltaTime / 0.25f;

	ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.f, 1.f);

	OurCamera->FieldOfView = FMath::Lerp<float>(90.f, 60.f, ZoomFactor);
	OurCameraSpringarm->TargetArmLength = FMath::Lerp<float>(400.f, 300.f, ZoomFactor);

	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += CameraInput.X;
	SetActorRotation(NewRotation);

	NewRotation = OurCameraSpringarm->GetComponentRotation();
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.f, -15.f);
	OurCameraSpringarm->SetWorldRotation(NewRotation);

	if (MovementInput.IsZero() == false)
	{
		MovementInput = MovementInput.GetSafeNormal() * 100.f;
		SetActorLocation(GetActorLocation()
						+ GetActorForwardVector() * MovementInput.X * DeltaTime
						+ GetActorRightVector() * MovementInput.Y * DeltaTime);
	}
}


void APGPawnWithCamera::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APGPawnWithCamera::ZoomIn);
	InputComponent->BindAction("ZoomIn", IE_Released, this, &APGPawnWithCamera::ZoomOut);
	
	InputComponent->BindAxis("Forward", this, &APGPawnWithCamera::MoveForward);
	InputComponent->BindAxis("Strafe", this, &APGPawnWithCamera::MoveRight);
	InputComponent->BindAxis("Pitch", this, &APGPawnWithCamera::PitchCamera);
	InputComponent->BindAxis("Yaw", this, &APGPawnWithCamera::YawCamera);
}
