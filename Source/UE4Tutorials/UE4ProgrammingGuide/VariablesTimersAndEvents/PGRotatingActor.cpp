// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "PGRotatingActor.h"


APGRotatingActor::APGRotatingActor()
{
	RootScene = CreateDefaultSubobject<USceneComponent>("Root Scene");
	RootComponent = RootScene;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetMobility(EComponentMobility::Movable);
	Mesh->AttachTo(RootComponent);

	DistanceToTargetTolerance = 500.f;
	BlendTime = 1.f;
	RotationAltitude = 100.f;
	RotationDistance = 50.f;
}


void APGRotatingActor::MoveToTargetWithBlend()
{
	if ((TargetActor->GetActorLocation() - GetActorLocation()).Size() > DistanceToTargetTolerance) return;

	GetWorldTimerManager().SetTimer(MovingWithBlendHandle, this, &APGRotatingActor::ComputeNewLocation, 0.05f, true);
}


void APGRotatingActor::ComputeNewLocation()
{
	FVector TargetLocation = TargetActor->GetActorLocation() + FVector(RotationDistance, 0.f, RotationAltitude) * TargetActor->GetActorForwardVector();

	float TimeElapsedRatio = GetWorldTimerManager().GetTimerElapsed(MovingWithBlendHandle) / BlendTime;
	float DistanceToTravel = TargetLocation.Size() * TimeElapsedRatio;

	SetActorLocation(GetActorLocation() + TargetLocation.GetClampedToMaxSize(DistanceToTravel));

	if (TimeElapsedRatio > 1.f) GetWorldTimerManager().ClearTimer(MovingWithBlendHandle);
}
