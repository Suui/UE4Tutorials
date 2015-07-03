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
	RotationOffset = FRotator(0.f, 0.f, 0.f);

	RotationSpeed = 90.f;
	bFaceRotationPoint = false;
}


/* Override */
void UPGRotatingMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RotationCenter = AttachParent->GetComponentLocation() + RotationCenterOffset;

	// Gets the UpVector for the created Rotator which orients X along the LocationOffset direction
	RotationAxis = UKismetMathLibrary::GetUpVector(UKismetMathLibrary::Conv_VectorToRotator(LocationOffset));

	LocationOffset = UKismetMathLibrary::RotateAngleAxis(LocationOffset, RotationSpeed * DeltaTime, RotationAxis);
	SetWorldLocation(RotationCenter + LocationOffset);

	if (bFaceRotationPoint)
		SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(RotationCenter + LocationOffset, RotationCenter) + RotationOffset);
}
