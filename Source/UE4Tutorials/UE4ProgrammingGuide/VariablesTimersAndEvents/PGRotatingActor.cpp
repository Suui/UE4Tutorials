// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "PGRotatingActor.h"
#include "Kismet/KismetMathLibrary.h"


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
	RotationSpeed = 5.f;
}


void APGRotatingActor::MoveToTargetWithBlend()
{
	if (TargetActor == nullptr)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Red, "No Target assigned for the PGRotatingActor");
		return;
	}
	if ((TargetActor->GetActorLocation() - GetActorLocation()).Size() > DistanceToTargetTolerance) return;

	TimerTicksLeft = BlendTime / 0.02f;
	GetWorldTimerManager().SetTimer(MovingWithBlendHandle, this, &APGRotatingActor::ComputeNewLocation, 0.02f, true);
}


void APGRotatingActor::ComputeNewLocation()
{
	FVector TargetLocation = TargetActor->GetActorLocation() + TargetActor->GetActorForwardVector() * RotationDistance;
	TargetLocation += FVector(0.f, 0.f, RotationAltitude);

	float DistanceToTravel = (TargetLocation - GetActorLocation()).Size() / TimerTicksLeft;
	SetActorLocation(GetActorLocation() + (TargetLocation - GetActorLocation()).GetClampedToMaxSize(DistanceToTravel));

	if (GEngine) GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Magenta, "Ratio: " + FString::SanitizeFloat(TimerTicksLeft));

	--TimerTicksLeft;
	if (TimerTicksLeft <= 0.f)
	{
		TimerElapsed = 0.f;
		GetWorldTimerManager().ClearTimer(MovingWithBlendHandle);
		GetWorldTimerManager().SetTimer(RotatingAroundActorHandle, this, &APGRotatingActor::StartRotatingAroundTarget, 0.02f, true);
	}
}


void APGRotatingActor::StartRotatingAroundTarget()
{
	FVector TargetLocation = TargetActor->GetActorLocation() + TargetActor->GetActorUpVector() * RotationAltitude;
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation));

	FVector RightDisplacement = GetActorLocation() + GetActorRightVector() * RotationSpeed;
	FVector NewLocationRelativeToTarget = (TargetLocation - RightDisplacement).GetClampedToMaxSize(RotationDistance);
	SetActorLocation(TargetLocation - NewLocationRelativeToTarget);

	TimerElapsed += 0.02f;
	if (TimerElapsed > 5.f)
	{
		TimerElapsed = 0.f;
		GetWorldTimerManager().ClearTimer(RotatingAroundActorHandle);
	}
}
