// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "LCPPMonster.h"


// Sets default values
ALCPPMonster::ALCPPMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 20;
	Health = 20;
	ExperienceDrop = 0;
	Loot = nullptr;
	BaseAttackDMG = 1;
	BaseAttackCD = 1.5f;
	TimeSinceLastBaseAttack = 0;

	SightSphereComp = CreateDefaultSubobject<USphereComponent>("Sight Sphere");
	SightSphereComp->AttachTo(RootComponent);

	BaseAttackRangeSphereComp = CreateDefaultSubobject<USphereComponent>("Base Attack Range");
	BaseAttackRangeSphereComp->AttachTo(RootComponent);
}


// Called when the game starts or when spawned
void ALCPPMonster::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ALCPPMonster::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


// Called to bind functionality to input
void ALCPPMonster::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

