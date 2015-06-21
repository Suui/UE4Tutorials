// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "PGMyActor.h"


// Sets default values
APGMyActor::APGMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APGMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APGMyActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

