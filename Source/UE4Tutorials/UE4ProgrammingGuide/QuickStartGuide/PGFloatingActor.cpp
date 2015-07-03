// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "PGFloatingActor.h"


APGFloatingActor::APGFloatingActor()
{
	PrimaryActorTick.bCanEverTick = true;
}


/* Override */
void APGFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();

	NewLocation.X += (FMath::Sin(RunningTime * MovementScale.X + DeltaTime) - FMath::Sin(RunningTime * MovementScale.X)) * MovementMagnitude.X;
	NewLocation.Y += (FMath::Sin(RunningTime * MovementScale.Y + DeltaTime) - FMath::Sin(RunningTime * MovementScale.Y)) * MovementMagnitude.Y;
	NewLocation.Z += (FMath::Sin(RunningTime * MovementScale.Z + DeltaTime) - FMath::Sin(RunningTime * MovementScale.Z)) * MovementMagnitude.Z;

	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}
