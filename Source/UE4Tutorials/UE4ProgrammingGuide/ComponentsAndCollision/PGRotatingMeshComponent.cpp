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

	RotationSpeed = 8.f;
	RotationAmplitude = 200.f;
}


void UPGRotatingMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

//	FVector ParentLocation = AttachParent->GetRelativeTransform().GetLocation();
//
//	FVector RotationCenter = ParentLocation + RotationCenterOffset;
//	if (GEngine) GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Magenta, RotationCenter.ToString());
//
//	FVector RotatingMeshLocation = RotationCenter + LocationOffset;
//	if (GEngine) GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Magenta, RotatingMeshLocation.ToString());
//
//	FVector Test = RotatingMeshLocation - RotationCenter;
//	if (GEngine) GEngine->AddOnScreenDebugMessage(2, 2.f, FColor::Magenta, Test.ToString());
//
//	FVector Displacement = Test.RotateAngleAxis(RotationSpeed * DeltaTime, AttachParent->GetUpVector());
//	SetRelativeLocation(RotationCenter + Displacement);


//	SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(GetComponentLocation(), RotationCenter) + RotationOffset);

//	FVector RightDisplacement = GetComponentLocation() + GetRightVector() * RotationSpeed;
//	FVector DisplacedLocation = (RotationCenter - RightDisplacement).GetClampedToSize(RotationAmplitude, RotationAmplitude);
//	SetWorldLocation(RotationCenter - DisplacedLocation);
}
