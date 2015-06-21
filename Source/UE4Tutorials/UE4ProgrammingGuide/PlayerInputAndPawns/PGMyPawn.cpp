// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "PGMyPawn.h"


/*----------------------------------------------------------------
- Initialization -
----------------------------------------------------------------*/

APGMyPawn::APGMyPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>("Our Camera");
	OurCamera->AttachTo(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-400.f, 0.f, 320.f));
	OurCamera->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>("Out Visible Component");
	OurVisibleComponent->AttachTo(RootComponent);

	MovementSpeed = 200.f;
}


/*----------------------------------------------------------------
- Private functions -
----------------------------------------------------------------*/

void APGMyPawn::MoveForward(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.f, 1.f) * MovementSpeed;
}


void APGMyPawn::Strafe(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.f, 1.f) * MovementSpeed;
}


void APGMyPawn::StartGrowing()
{
	bIsGrowing = true;
}


void APGMyPawn::StopGrowing()
{
	bIsGrowing = false;
}


/*----------------------------------------------------------------
- Public functions -
----------------------------------------------------------------*/

/* Override */
void APGMyPawn::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	InputComponent->BindAction("Grow", IE_Pressed, this, &APGMyPawn::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &APGMyPawn::StopGrowing);

	InputComponent->BindAxis("Forward", this, &APGMyPawn::MoveForward);
	InputComponent->BindAxis("Strafe", this, &APGMyPawn::Strafe);
}


/* Override */
void APGMyPawn::Tick(float DeltaTime)
{
	float CurrentXScale = OurVisibleComponent->GetComponentScale().X;

	if (bIsGrowing)
		CurrentXScale += DeltaTime;
	else 
		CurrentXScale -= DeltaTime * 0.5f;

	CurrentXScale = FMath::Clamp(CurrentXScale, 1.0f, 2.0f);
	OurVisibleComponent->SetWorldScale3D(FVector(CurrentXScale));

	if (CurrentVelocity.IsZero() == false)
	{
		FVector NewLocation = GetActorLocation() + CurrentVelocity * DeltaTime;
		SetActorLocation(NewLocation);
	}
}
