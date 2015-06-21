// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PGMyActor.generated.h"

UCLASS()
class UE4TUTORIALS_API APGMyActor : public AActor
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 TotalDamge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageTimeInSeconds;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Damage")
	float DamagePerSecond;


private:

	void CalculateValues();


public:

	APGMyActor();

	void PostInitProperties() override;

	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
