// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PGRotatingActor.generated.h"

UCLASS()
class UE4TUTORIALS_API APGRotatingActor : public AActor
{
	GENERATED_BODY()

	FTimerHandle MovingWithBlendHandle, RotatingAroundActorHandle;
	float TimerElapsed = 0.f;
	float TimerTicksLeft = 0.f;


public:

	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* RootScene;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = RotatingActorProperties)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RotatingActorProperties)
	AActor* TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RotatingActorProperties)
	float DistanceToTargetTolerance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RotatingActorProperties)
	float BlendTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RotatingActorProperties)
	float RotationAltitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RotatingActorProperties)
	float RotationDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RotatingActorProperties)
	float RotationSpeed;


private:

	UFUNCTION(BlueprintCallable, Category = RotatingActorFunctions)
	void MoveToTargetWithBlend();

	void ComputeNewLocation();

	void StartRotatingAroundTarget();


public:

	APGRotatingActor();
};
