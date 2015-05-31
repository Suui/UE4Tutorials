// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "LCPPMonster.h"
#include <LearningCPP/Character/LearningCPPCharacter.h>


// Sets default values
ALCPPMonster::ALCPPMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 20;
	Health = 20;
	ExperienceDrop = 0;
	Loot = nullptr;
	BaseAttackDMG = 1;
	BaseAttackCD = 1.5f;
	TimeSinceLastBaseAttack = 0;

	SightSphereComp = CreateDefaultSubobject<USphereComponent>("Sight Sphere");
	SightSphereComp->AttachTo(RootComponent);
	SightSphereComp->OnComponentBeginOverlap.AddDynamic(this, &ALCPPMonster::StartChasing);
	SightSphereComp->OnComponentEndOverlap.AddDynamic(this, &ALCPPMonster::StopChasing);

	BaseAttackRangeSphereComp = CreateDefaultSubobject<USphereComponent>("Base Attack Range");
	BaseAttackRangeSphereComp->AttachTo(RootComponent);
}


void ALCPPMonster::StartChasing(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ALearningCPPCharacter>(OtherActor))
		bEnemyInSight = true;
}


void ALCPPMonster::StopChasing(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (Cast<ALearningCPPCharacter>(OtherActor))
		bEnemyInSight = false;
}


// Called when the game starts or when spawned
void ALCPPMonster::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ALCPPMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bEnemyInSight)
		ChasePlayer(DeltaTime);
}


void ALCPPMonster::ChasePlayer(float DeltaTime)
{
	ALearningCPPCharacter* PlayerCharacter = Cast<ALearningCPPCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (PlayerCharacter == nullptr) return;

	FVector DirectionToPlayer = PlayerCharacter->GetActorLocation() - GetActorLocation();
	DirectionToPlayer.Normalize();
	AddMovementInput(DirectionToPlayer, Speed * DeltaTime);

	// He will stand right even if the player is in a different altitude, by only rotating in the Z axis (Yaw).
	FRotator RotationToPlayer = DirectionToPlayer.Rotation();
	RotationToPlayer.Pitch = 0;		// Won't rotate in the Y axis.
	RotationToPlayer.Roll = 0;		// Won't rotate in the X axis.
	RootComponent->SetWorldRotation(RotationToPlayer);
}


// Called to bind functionality to input
void ALCPPMonster::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

