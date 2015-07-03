// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "PGRotatingMeshComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Suui), meta=(BlueprintSpawnableComponent))
class UE4TUTORIALS_API UPGRotatingMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

	FVector RotationCenter, RotationAxis;


public:

	/* Offset added to the RotationCenter which is the Pivot of the parent component. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation Mesh Component Properties")
	FVector RotationCenterOffset;

	/* Offset that determines the amplitude of the rotation and its axis of rotation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation Mesh Component Properties")
	FVector LocationOffset;

	/* Offset added to the Rotation of the rotating component (in WorldRotation). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation Mesh Component Properties")
	FRotator RotationOffset;

	/* In degrees per second. Negative values reverse the rotation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation Mesh Component Properties")
	float RotationSpeed;

	/* Whether the rotating component should always face to the RotationCenter (+ RotationOffset) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation Mesh Component Properties")
	bool bFaceRotationPoint;

	UPGRotatingMeshComponent();

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
