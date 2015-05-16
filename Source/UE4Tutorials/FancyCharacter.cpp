// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "FancyCharacter.h"


// Sets default values
AFancyCharacter::AFancyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFancyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFancyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AFancyCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

