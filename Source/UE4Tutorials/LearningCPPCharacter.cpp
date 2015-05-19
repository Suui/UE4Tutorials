// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "LearningCPPCharacter.h"


// Sets default values
ALearningCPPCharacter::ALearningCPPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraSensitivity = 120.0f;
	bInvertCameraXAxis = false;
	bInvertCameraYAxis = true;
}


// Called when the game starts or when spawned
void ALearningCPPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ALearningCPPCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


// Called to bind functionality to input
void ALearningCPPCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	check(InputComponent);
	InputComponent->BindAxis("Forward", this, &ALearningCPPCharacter::MoveForward);
	InputComponent->BindAxis("Strafe", this, &ALearningCPPCharacter::Strafe);
	InputComponent->BindAxis("Yaw", this, &ALearningCPPCharacter::Yaw);
	InputComponent->BindAxis("Pitch", this, &ALearningCPPCharacter::Pitch);
}


void ALearningCPPCharacter::MoveForward(float Amount)
{
	if (Controller != nullptr && Amount != 0)
	{
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, Amount);
	}
}


void ALearningCPPCharacter::Strafe(float Amount)
{
	if (Controller != nullptr && Amount != 0)
	{
		FVector Right = GetActorRightVector();
		AddMovementInput(Right, Amount);
	}
}


void ALearningCPPCharacter::Yaw(float Amount)
{
	if (Controller != nullptr && Amount != 0)
	{
		if (bInvertCameraXAxis) 
			Amount *= -1.0f;
		AddControllerYawInput(CameraSensitivity * Amount * GetWorld()->GetDeltaSeconds());
	}
}


void ALearningCPPCharacter::Pitch(float Amount)
{
	if (Controller != nullptr && Amount != 0)
	{
		if (bInvertCameraYAxis) 
			Amount *= -1.0f;
		AddControllerPitchInput(CameraSensitivity * Amount * GetWorld()->GetDeltaSeconds());
	}
}
