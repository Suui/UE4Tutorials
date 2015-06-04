// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "LCPPMeleeWeapon.h"
#include <LearningCPP/Mobs/LCPPMonster.h>


// Sets default values
ALCPPMeleeWeapon::ALCPPMeleeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackDamage = 5;
	bIsSwinging = false;
	WeaponHolder = nullptr;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Scene Component");

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("Weapon Mesh");
	WeaponMesh->AttachTo(RootComponent);

	WeaponBoxComp = CreateDefaultSubobject<UBoxComponent>("Weapon Boundaries Box Component");
	WeaponBoxComp->AttachTo(WeaponMesh);
	WeaponBoxComp->OnComponentBeginOverlap.AddDynamic(this, &ALCPPMeleeWeapon::Hit);
}


void ALCPPMeleeWeapon::Hit(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComponent != OtherActor->GetRootComponent()) return;

	if (bIsSwinging && OtherActor != WeaponHolder && TargetsHit.Contains(OtherActor) == false)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(0, 0.5f, FColor::Magenta, "Target Hit!");
		OtherActor->TakeDamage(AttackDamage + WeaponHolder->BaseAttackDMG, FDamageEvent(), nullptr, this);
		TargetsHit.Add(OtherActor);
	}
}


void ALCPPMeleeWeapon::Rest()
{
	TargetsHit.Empty();
	bIsSwinging = false;
}


// Called when the game starts or when spawned
void ALCPPMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ALCPPMeleeWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void ALCPPMeleeWeapon::Swing()
{
	TargetsHit.Empty();
	bIsSwinging = true;
}