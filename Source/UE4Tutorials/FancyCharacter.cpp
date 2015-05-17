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
	check(InputComponent);
	InputComponent->BindAxis("Forward", this, &AFancyCharacter::MoveForward);
	InputComponent->BindAxis("Strafe", this, &AFancyCharacter::Strafe);
	InputComponent->BindAxis("Yaw", this, &AFancyCharacter::Yaw);
	InputComponent->BindAxis("Pitch", this, &AFancyCharacter::Pitch);
}


void AFancyCharacter::MoveForward(float Amount)
{
	if (Controller != nullptr && Amount != 0)
	{
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, Amount);
	}
}


void AFancyCharacter::Strafe(float Amount)
{
	if (Controller != nullptr && Amount != 0)
	{
		FVector Right = GetActorRightVector();
		AddMovementInput(Right, Amount);
	}
}


void AFancyCharacter::Yaw(float Amount)
{
	if (Controller != nullptr && Amount != 0)
		AddControllerYawInput(YAW_PITCH_MULTIPLIER * Amount * GetWorld()->GetDeltaSeconds());
}


void AFancyCharacter::Pitch(float Amount)
{
	if (Controller != nullptr && Amount != 0)
		AddControllerPitchInput(YAW_PITCH_MULTIPLIER * Amount * GetWorld()->GetDeltaSeconds());
}
