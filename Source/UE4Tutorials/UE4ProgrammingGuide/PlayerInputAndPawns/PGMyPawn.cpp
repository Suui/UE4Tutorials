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

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>("Out Visible Component");
	OurVisibleComponent->AttachTo(RootComponent);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	CameraBoom->SetRelativeRotation(FRotator(0.f, -30.f, 0.f));

	OurCamera = CreateDefaultSubobject<UCameraComponent>("Our Camera");
	OurCamera->AttachTo(CameraBoom);

	MovementSpeed = 200.f;
}


/*----------------------------------------------------------------
- Private functions -
----------------------------------------------------------------*/

void APGMyPawn::MoveForward(float AxisValue)
{
	ForwardVelocity = GetActorForwardVector() * FMath::Clamp(AxisValue, -1.f, 1.f) * MovementSpeed;
}


void APGMyPawn::Strafe(float AxisValue)
{
	StrafeVelocity = GetActorRightVector() * FMath::Clamp(AxisValue, -1.f, 1.f) * MovementSpeed;
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

	if (ForwardVelocity.IsZero() == false || StrafeVelocity.IsZero() == false)
		SetActorLocation(GetActorLocation() + (ForwardVelocity + StrafeVelocity).GetClampedToMaxSize(MovementSpeed) * DeltaTime);
}
