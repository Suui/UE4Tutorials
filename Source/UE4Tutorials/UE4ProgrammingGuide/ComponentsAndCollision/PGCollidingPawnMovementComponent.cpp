// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "PGCollidingPawnMovementComponent.h"


void UPGCollidingPawnMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PawnOwner == nullptr || UpdatedComponent == nullptr || ShouldSkipUpdate(DeltaTime)) return;

	// ConsumeInputVector reports and clears the value of a built-in variable that we will use to store our movement inputs.
	FVector DesiredMovement = ConsumeInputVector().GetClampedToMaxSize(1.f) * DeltaTime * 200.f;

	if (DesiredMovement.IsNearlyZero() == false)
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovement, UpdatedComponent->GetComponentRotation(), true, Hit);
		// SafeMoveUpdatedComponent uses Unreal Engine physics to move our Pawn Movement Component while respecting solid barriers.

		if (Hit.IsValidBlockingHit())
			SlideAlongSurface(DesiredMovement, 1.f - Hit.Time, Hit.Normal, Hit);
	}
}
