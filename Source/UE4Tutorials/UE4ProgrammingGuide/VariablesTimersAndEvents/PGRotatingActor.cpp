// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "PGRotatingActor.h"
#include "Kismet/KismetMathLibrary.h"


/*----------------------------------------------------------------
- Initialization -
----------------------------------------------------------------*/

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


/*----------------------------------------------------------------
- Private functions -
----------------------------------------------------------------*/

void APGRotatingActor::ComputeLocationToActor()
{
	FVector TargetLocation = TargetActor->GetActorLocation() + TargetActor->GetActorForwardVector() * RotationDistance + TargetActor->GetActorUpVector() * RotationAltitude;
	float DistanceToTravel = (TargetLocation - GetActorLocation()).Size() / TimerTicksLeft;

	SetActorLocation(GetActorLocation() + (TargetLocation - GetActorLocation()).GetClampedToMaxSize(DistanceToTravel));

	--TimerTicksLeft;
	if (TimerTicksLeft <= 0.f)
	{
		TimerElapsed = 0.f;
		GetWorldTimerManager().ClearTimer(MovingWithBlendHandle);
		GetWorldTimerManager().SetTimer(RotatingAroundActorHandle, this, &APGRotatingActor::RotateAroundActor, TIMER_RATE, true);
	}
}


void APGRotatingActor::ComputeLocationToTarget()
{
	float DistanceToTravel = (TargetVector - GetActorLocation()).Size() / TimerTicksLeft;

	SetActorLocation(GetActorLocation() + (TargetVector - GetActorLocation()).GetClampedToMaxSize(DistanceToTravel));

	--TimerTicksLeft;
	if (TimerTicksLeft <= 0.f)
	{
		TimerElapsed = 0.f;
		GetWorldTimerManager().ClearTimer(MovingWithBlendHandle);
	}
}


void APGRotatingActor::RotateAroundActor()
{
	FVector TargetLocation = TargetActor->GetActorLocation() + TargetActor->GetActorUpVector() * RotationAltitude;
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation));

	FVector RightDisplacement = GetActorLocation() + GetActorRightVector() * RotationSpeed;
	FVector NewLocationRelativeToTarget = (TargetLocation - RightDisplacement).GetClampedToMaxSize(RotationDistance);
	SetActorLocation(TargetLocation - NewLocationRelativeToTarget);

	TimerElapsed += TIMER_RATE;
	if (TimerElapsed > TimeToRotate)
	{
		TimerElapsed = 0.f;
		GetWorldTimerManager().ClearTimer(RotatingAroundActorHandle);
		MoveToTargetWithBlend(OriginalLocation);
	}
}


/*----------------------------------------------------------------
- Public functions -
----------------------------------------------------------------*/

void APGRotatingActor::MoveToActorWithBlend(AActor* Target)
{
	if ((Target->GetActorLocation() - GetActorLocation()).Size() > DistanceToTargetTolerance) return;

	OriginalLocation = GetActorLocation();
	TargetActor = Target;
	TimerTicksLeft = BlendTime / TIMER_RATE;

	GetWorldTimerManager().SetTimer(MovingWithBlendHandle, this, &APGRotatingActor::ComputeLocationToActor, TIMER_RATE, true);
}


void APGRotatingActor::MoveToTargetWithBlend(FVector Target)
{
	if ((Target - GetActorLocation()).Size() > DistanceToTargetTolerance) return;

	TargetVector = Target;
	TimerTicksLeft = BlendTime / TIMER_RATE;

	GetWorldTimerManager().SetTimer(MovingWithBlendHandle, this, &APGRotatingActor::ComputeLocationToTarget, TIMER_RATE, true);
}
