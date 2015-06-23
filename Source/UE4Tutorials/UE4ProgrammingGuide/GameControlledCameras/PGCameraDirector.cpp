// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "PGCameraDirector.h"
#include "Kismet/GameplayStatics.h"


APGCameraDirector::APGCameraDirector()
{
	PrimaryActorTick.bCanEverTick = true;

}


void APGCameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeToNextCameraChange -= DeltaTime;

	if (TimeToNextCameraChange <= 0.f)
	{
		TimeToNextCameraChange += TIME_BETWEEN_CAMERA_CHANGES;

		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (OurPlayerController)
		{
			if (OurPlayerController->GetViewTarget() != CameraOne && CameraOne != nullptr)
				OurPlayerController->SetViewTarget(CameraOne);
			else if (OurPlayerController->GetViewTarget() != CameraTwo && CameraTwo != nullptr)
				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SMOOTH_BLEND_TIME);
		}
	}
}
