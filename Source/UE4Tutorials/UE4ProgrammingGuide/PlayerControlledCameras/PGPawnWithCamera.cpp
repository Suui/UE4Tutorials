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


void APGPawnWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APGPawnWithCamera::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

