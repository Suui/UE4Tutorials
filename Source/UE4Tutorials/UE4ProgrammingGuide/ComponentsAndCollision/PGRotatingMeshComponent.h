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



public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation Mesh Component Properties")
	FVector RotationCenterOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation Mesh Component Properties")
	FVector LocationOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation Mesh Component Properties")
	FRotator RotationOffset;

	/* Negative values reverse the rotation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation Mesh Component Properties")
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation Mesh Component Properties")
	float RotationAmplitude;

	UPGRotatingMeshComponent();

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
