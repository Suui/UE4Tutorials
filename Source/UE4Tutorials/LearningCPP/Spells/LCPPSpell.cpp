// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "LCPPSpell.h"
#include "LearningCPP/Mobs/LCPPMonster.h"


// Sets default values
ALCPPSpell::ALCPPSpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ParticleVisualization = CreateDefaultSubobject<UParticleSystemComponent>("Particle Visualization");
	RootComponent = ParticleVisualization;

	ProxBox = CreateDefaultSubobject<UBoxComponent>("Proximity Box");
	ProxBox->AttachTo(RootComponent);

	Duration = 3.f;
	TimeAlive = 0.f;
	DamagePerSec = 1;
}


// Called when the game starts or when spawned
void ALCPPSpell::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ALCPPSpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> ActorsAffected;
	ProxBox->GetOverlappingActors(ActorsAffected);

	for (int i = 0; i < ActorsAffected.Num(); ++i)
	{
		if (ActorsAffected[i] != Caster)
		{
			ALCPPMonster* Monster = Cast<ALCPPMonster>(ActorsAffected[i]);
			if (Monster != nullptr && ProxBox->IsOverlappingComponent(Monster->GetCapsuleComponent()))
				Monster->TakeDamage(DamagePerSec * DeltaTime, FDamageEvent(), nullptr, this);
		}
	}

	TimeAlive += DeltaTime;
	if (TimeAlive > Duration) Destroy();
}


void ALCPPSpell::SetCaster(AActor* Caster)
{
	this->Caster = Caster;
	AttachRootComponentTo(Caster->GetRootComponent());
}
