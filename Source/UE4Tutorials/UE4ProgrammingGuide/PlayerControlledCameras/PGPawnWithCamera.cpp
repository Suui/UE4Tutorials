// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "PGPawnWithCamera.h"


/*----------------------------------------------------------------
- Initialization -
----------------------------------------------------------------*/


APGPawnWithCamera::APGPawnWithCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root Component");

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->AttachTo(RootComponent);

	OurCameraSpringarm = CreateDefaultSubobject<USpringArmComponent>("Camera Spring Arm");
	OurCameraSpringarm->AttachTo(RootComponent);
	OurCameraSpringarm->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 50.f), FRotator(-60.f, 0.f, 0.f));
	OurCameraSpringarm->TargetArmLength = 400.f;
	OurCameraSpringarm->bEnableCameraLag = true;
	OurCameraSpringarm->CameraLagSpeed = 3.f;

	OurCamera = CreateDefaultSubobject<UCameraComponent>("Game Camera");
	OurCamera->AttachTo(OurCameraSpringarm);

	static ConstructorHelpers::FObjectFinder<UCurveVector> CurveAsset(TEXT("/Game/UE4ProgrammingGuide/CU_CameraMotion.CU_CameraMotion"));
	if (CurveAsset.Succeeded())
		CameraMotionCurve = CurveAsset.Object;

	WalkingSpeed = 200.f;
	RunningSpeed = 350.f;
	MovementSpeed = WalkingSpeed;
	CameraMotionFactor = 0.1f;
}


/* Override */
void APGPawnWithCamera::PostInitProperties()
{
	Super::PostInitProperties();

	CalculateMovementSpeed();
}


/*----------------------------------------------------------------
- Protected functions -
----------------------------------------------------------------*/

void APGPawnWithCamera::CalculateMovementSpeed()
{
	MovementSpeed = WalkingSpeed;
}


void APGPawnWithCamera::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp(AxisValue, -1.f, 1.f);
}


void APGPawnWithCamera::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp(AxisValue, -1.f, 1.f);
}


void APGPawnWithCamera::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}


void APGPawnWithCamera::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}


void APGPawnWithCamera::ZoomIn()
{
	bZoomingIn = true;
}


void APGPawnWithCamera::ZoomOut()
{
	bZoomingIn = false;
}


void APGPawnWithCamera::Run()
{
	MovementSpeed = RunningSpeed;
}


void APGPawnWithCamera::StopRunning()
{
	MovementSpeed = WalkingSpeed;
}


/*----------------------------------------------------------------
- Public functions -
----------------------------------------------------------------*/

/* Override */
void APGPawnWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bZoomingIn)
		ZoomFactor += DeltaTime / 0.5f;
	else
		ZoomFactor -= DeltaTime / 0.25f;

	ZoomFactor = FMath::Clamp(ZoomFactor, 0.f, 1.f);

	OurCamera->FieldOfView = FMath::Lerp(90.f, 60.f, ZoomFactor);
	OurCameraSpringarm->TargetArmLength = FMath::Lerp(400.f, 300.f, ZoomFactor);

	if (CameraMotionCurve != nullptr)
		CameraMotion = CameraMotionCurve->GetVectorValue(FMath::Fmod(UGameplayStatics::GetRealTimeSeconds(GetWorld()), 10.f));

	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += CameraInput.X + CameraMotion.X * CameraMotionFactor;
	SetActorRotation(NewRotation);

	NewRotation = OurCameraSpringarm->GetComponentRotation();
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y + CameraMotion.Y * CameraMotionFactor, -85.f, 85.f);
	OurCameraSpringarm->SetWorldRotation(NewRotation);

	if (MovementInput.IsZero() == false)
	{
		MovementInput = MovementInput.GetSafeNormal() * MovementSpeed;
		SetActorLocation(GetActorLocation()
						+ GetActorForwardVector() * MovementInput.X * DeltaTime
						+ GetActorRightVector() * MovementInput.Y * DeltaTime);
	}
}


/* Override */
void APGPawnWithCamera::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APGPawnWithCamera::ZoomIn);
	InputComponent->BindAction("ZoomIn", IE_Released, this, &APGPawnWithCamera::ZoomOut);
	InputComponent->BindAction("Run", IE_Pressed, this, &APGPawnWithCamera::Run);
	InputComponent->BindAction("Run", IE_Released, this, &APGPawnWithCamera::StopRunning);

	InputComponent->BindAxis("Forward", this, &APGPawnWithCamera::MoveForward);
	InputComponent->BindAxis("Strafe", this, &APGPawnWithCamera::MoveRight);
	InputComponent->BindAxis("Pitch", this, &APGPawnWithCamera::PitchCamera);
	InputComponent->BindAxis("Yaw", this, &APGPawnWithCamera::YawCamera);
}


#if WITH_EDITOR
/* Override */
void APGPawnWithCamera::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	CalculateMovementSpeed();
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
