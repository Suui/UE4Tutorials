// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "PGCameraDirector.h"


APGCameraDirector::APGCameraDirector()
{
	PrimaryActorTick.bCanEverTick = true;
}


void APGCameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Cameras.Num() == 0) return;

	TimeToNextCameraChange -= DeltaTime;

	if (TimeToNextCameraChange < 0.f)
	{
		Index = (Index + 1) % Cameras.Num();
		TimeToNextCameraChange = Cameras[Index].TimeBeforeChangingToNextCamera;
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		
		if (PlayerController && Cameras[Index].Camera != nullptr)
			PlayerController->SetViewTargetWithBlend(Cameras[Index].Camera, Cameras[Index].SmoothBlendTime);
	}
}
