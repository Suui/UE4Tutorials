// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "PGCollidingPawn.h"
#include "PGCollidingPawnMovementComponent.h"


/*----------------------------------------------------------------
- Initialization -
----------------------------------------------------------------*/

APGCollidingPawn::APGCollidingPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>("Collision Sphere");
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.f);
	SphereComponent->SetCollisionProfileName("Pawn");
	
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>("Visual Representation");
	SphereVisual->AttachTo(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/Assets/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.f, 0.f, -40.f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>("Movement Particles");
	OurParticleSystem->AttachTo(SphereVisual);
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(-20.f, 0.f, 20.f));
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/Assets/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
		OurParticleSystem->SetTemplate(ParticleAsset.Object);

	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>("Camera Attachment Arm");
	SpringArm->AttachTo(RootComponent);
	SpringArm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 400.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.f;

	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>("Actual Camera");
	Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);

	OurMovementComponent = CreateDefaultSubobject<UPGCollidingPawnMovementComponent>("Custom Movement Component");
	OurMovementComponent->UpdatedComponent = RootComponent;
}


/*----------------------------------------------------------------
- Protected functions -
----------------------------------------------------------------*/

void APGCollidingPawn::MoveForward(float AxisValue)
{
	if (OurMovementComponent != nullptr && (OurMovementComponent->UpdatedComponent == RootComponent))
		OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
}


void APGCollidingPawn::MoveRight(float AxisValue)
{
	if (OurMovementComponent != nullptr && (OurMovementComponent->UpdatedComponent == RootComponent))
		OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
}


void APGCollidingPawn::Turn(float AxisValue)
{
	SetActorRotation(GetActorRotation() + FRotator(0.f, AxisValue, 0.f));
}


void APGCollidingPawn::ToggleParticle()
{
	if (OurParticleSystem != nullptr && OurParticleSystem->Template != nullptr)
		OurParticleSystem->ToggleActive();
}


/*----------------------------------------------------------------
- Public functions -
----------------------------------------------------------------*/

/* Override */
void APGCollidingPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("ToggleParticle", IE_Pressed, this, &APGCollidingPawn::ToggleParticle);

	InputComponent->BindAxis("Forward", this, &APGCollidingPawn::MoveForward);
	InputComponent->BindAxis("Strafe", this, &APGCollidingPawn::MoveRight);
	InputComponent->BindAxis("Yaw", this, &APGCollidingPawn::Turn);
}


/* Override */
inline UPawnMovementComponent* APGCollidingPawn::GetMovementComponent() const
{
	return OurMovementComponent;
}
