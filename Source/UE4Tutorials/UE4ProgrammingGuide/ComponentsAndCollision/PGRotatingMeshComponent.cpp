// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "PGRotatingMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"


UPGRotatingMeshComponent::UPGRotatingMeshComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bAutoActivate = true;

	LocationOffset = FVector(0.f, 0.f, 0.f);
	RotationOffset = FRotator(0.f, 0.f, 0.f);

	RotationSpeed = 8.f;
	RotationAmplitude = 200.f;
}


void UPGRotatingMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector RotationCenter = AttachParent->GetComponentLocation() + LocationOffset;
//	SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(GetComponentLocation(), RotationCenter) + RotationOffset);

	FVector RightDisplacement = GetComponentLocation() + GetRightVector() * RotationSpeed;
	FVector DisplacedLocation = (RotationCenter - RightDisplacement).GetClampedToSize(RotationAmplitude, RotationAmplitude);
	SetWorldLocation(RotationCenter - DisplacedLocation);
}
