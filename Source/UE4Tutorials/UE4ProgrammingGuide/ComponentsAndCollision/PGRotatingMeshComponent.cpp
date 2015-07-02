// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "PGRotatingMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"


UPGRotatingMeshComponent::UPGRotatingMeshComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bAutoActivate = true;

	RotationCenterOffset = FVector(0.f, 0.f, 0.f);
	LocationOffset = FVector(0.f, 0.f, 0.f);

	RotationSpeed = 90.f;
}


/* Override */
void UPGRotatingMeshComponent::BeginPlay()
{
	RotationCenter = AttachParent->GetRelativeTransform().GetLocation() + RotationCenterOffset;

	// Gets the UpVector for the created Rotator which orients X along the LocationOffset direction
	RotationAxis = UKismetMathLibrary::GetUpVector(UKismetMathLibrary::Conv_VectorToRotator(LocationOffset));
}


/* Override */
void UPGRotatingMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	LocationOffset = UKismetMathLibrary::RotateAngleAxis(LocationOffset, RotationSpeed * DeltaTime, RotationAxis);
	SetRelativeLocation(RotationCenter + LocationOffset);
}
