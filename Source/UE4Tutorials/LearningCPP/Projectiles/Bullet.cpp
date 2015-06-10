// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "Bullet.h"


/// CONSTRUCTORS ///
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Damage = 1;

	ProxSphere = CreateDefaultSubobject<USphereComponent>("Proximity Sphere");
	RootComponent = ProxSphere;
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ABullet::Prox);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->AttachTo(ProxSphere);
}


/// PRIVATE FUNCTIONS ///
void ABullet::Prox_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSwpp, const FHitResult& SweepResult)
{
	// Don't collide with anything other than the other actor's RootComponent
	if (OtherComponent != OtherActor->GetRootComponent()) return;

	OtherActor->TakeDamage(Damage, FDamageEvent(), nullptr, this);
	Destroy();
}


/// PUBLIC FUNCTIONS ///
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABullet::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

