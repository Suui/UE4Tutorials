// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "PGFloatingActor.h"


APGFloatingActor::APGFloatingActor()
{
	PrimaryActorTick.bCanEverTick = true;
}


void APGFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	float DeltaHeight = FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime);

	NewLocation.Z += DeltaHeight * HeightScale;
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}
