// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LCPPSpell.generated.h"


UCLASS()
class UE4TUTORIALS_API ALCPPSpell : public AActor
{
	GENERATED_BODY()


public:

	AActor* Caster;
	float TimeAlive;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = SpellProperties)
	UBoxComponent* ProxBox;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = SpellProperties)
	UParticleSystemComponent* ParticleVisualization;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpellProperties)
	int32 DamagePerSec;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpellProperties)
	float Duration;

	ALCPPSpell();

	virtual void Tick(float DeltaSeconds) override;

	void SetCaster(AActor* Caster);
};
