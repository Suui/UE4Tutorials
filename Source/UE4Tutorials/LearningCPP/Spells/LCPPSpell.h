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

	// Sets default values for this actor's properties
	ALCPPSpell();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void SetCaster(AActor* Caster);
};
