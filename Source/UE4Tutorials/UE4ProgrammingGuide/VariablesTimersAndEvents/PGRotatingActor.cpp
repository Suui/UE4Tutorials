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
	RotationAltitude = 0.f;
	RotationDistance = 50.f;
}


void APGRotatingActor::MoveToTargetWithBlend()
{
	if (TargetActor == nullptr)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Red, "No Target assigned for the PGRotatingActor");
		return;
	}
	if ((TargetActor->GetActorLocation() - GetActorLocation()).Size() > DistanceToTargetTolerance) return;

	GetWorldTimerManager().SetTimer(MovingWithBlendHandle, this, &APGRotatingActor::ComputeNewLocation, 0.02f, true);
}


void APGRotatingActor::ComputeNewLocation()
{
	FVector TargetLocation = TargetActor->GetActorLocation() + TargetActor->GetActorForwardVector() * RotationDistance;
	TargetLocation += FVector(0.f, 0.f, RotationAltitude);

	TimerElapsed += 0.02f;
	float TimeElapsedRatio = TimerElapsed / BlendTime;
	float DistanceToTravel = (TargetLocation - GetActorLocation()).Size() * FMath::Min(TimeElapsedRatio, 1.f);

	SetActorLocation(GetActorLocation() + (TargetLocation - GetActorLocation()).GetClampedToMaxSize(DistanceToTravel));

	if (TimeElapsedRatio >= 1.f)
	{
		TimerElapsed = 0.f;
		GetWorldTimerManager().ClearTimer(MovingWithBlendHandle);
		StartRotatingAroundTarget();
	}
}


void APGRotatingActor::StartRotatingAroundTarget()
{

}
