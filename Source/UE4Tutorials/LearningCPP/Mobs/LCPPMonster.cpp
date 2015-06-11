// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "LCPPMonster.h"
#include <LearningCPP/Character/LearningCPPCharacter.h>
#include <LearningCPP/Weapons/LCPPMeleeWeapon.h>
#include <LearningCPP/Projectiles/LCPPBullet.h>


// Sets default values
ALCPPMonster::ALCPPMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bEnemyInSight = false;
	bEnemyInAttackRange = false;

	Speed = 20;
	Health = 20;
	ExperienceDrop = 0;
	Loot = nullptr;
	BaseAttackDMG = 1;
	BaseAttackCD = 1.5f;
	TimeSinceLastBaseAttack = BaseAttackCD;
	EnableAttackAnim = false;

	SightSphereComp = CreateDefaultSubobject<USphereComponent>("Sight Sphere");
	SightSphereComp->AttachTo(RootComponent);
	SightSphereComp->OnComponentBeginOverlap.AddDynamic(this, &ALCPPMonster::StartChasing);
	SightSphereComp->OnComponentEndOverlap.AddDynamic(this, &ALCPPMonster::StopChasing);

	BaseAttackRangeSphereComp = CreateDefaultSubobject<USphereComponent>("Base Attack Range");
	BaseAttackRangeSphereComp->AttachTo(RootComponent);
	BaseAttackRangeSphereComp->OnComponentBeginOverlap.AddDynamic(this, &ALCPPMonster::StartAttacking);
	BaseAttackRangeSphereComp->OnComponentEndOverlap.AddDynamic(this, &ALCPPMonster::StopAttacking);
}


void ALCPPMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (MeleeWeaponBP == nullptr) return;

	MeleeWeaponInstance = GetWorld()->SpawnActor<ALCPPMeleeWeapon>(MeleeWeaponBP, FVector(), FRotator());

	if (MeleeWeaponInstance != nullptr)
	{
		GetMesh()->GetSocketByName("RightHandSocket")->AttachActor(MeleeWeaponInstance, GetMesh());
		auto Sword = Cast<ALCPPMeleeWeapon>(MeleeWeaponInstance);
		if (Sword != nullptr) Sword->WeaponHolder = this;
	}

}


void ALCPPMonster::StartChasing(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ALearningCPPCharacter>(OtherActor)) bEnemyInSight = true;
}


void ALCPPMonster::StopChasing(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (Cast<ALearningCPPCharacter>(OtherActor)) bEnemyInSight = false;
}


void ALCPPMonster::StartAttacking(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ALearningCPPCharacter>(OtherActor)) bEnemyInAttackRange = true;
}


void ALCPPMonster::StopAttacking(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (Cast<ALearningCPPCharacter>(OtherActor)) bEnemyInAttackRange = false;
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

	TimeSinceLastBaseAttack += DeltaTime;
	if (bEnemyInSight)
	{
		if (bEnemyInAttackRange)
		{
			if (TimeSinceLastBaseAttack >= BaseAttackCD)
			{
				// Attack is Called in the Anim Graph and I kinda don't like it
				EnableAttackAnim = true;
				TimeSinceLastBaseAttack = 0.f;
			}
			return;
		}
		if (EnableAttackAnim) return;
		ChasePlayer(DeltaTime);
	}
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


void ALCPPMonster::Attack()
{
	auto Sword = Cast<ALCPPMeleeWeapon>(MeleeWeaponInstance);
	
	if (Sword != nullptr) 
		Sword->Swing();
	else if (BulletBP)
	{
		FVector NozzleLocation = GetMesh()->GetBoneLocation("RightHandIndex4");
		NozzleLocation += GetActorForwardVector() * 20;
		ALearningCPPCharacter* PlayerCharacter = Cast<ALearningCPPCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (PlayerCharacter == nullptr) return;

		FVector DirectionToPlayer = PlayerCharacter->GetActorLocation() - NozzleLocation;
		DirectionToPlayer.Normalize();
		ALCPPBullet* Bullet = GetWorld()->SpawnActor<ALCPPBullet>(BulletBP, NozzleLocation, RootComponent->GetComponentRotation());
		
		if (Bullet != nullptr)
		{
			Bullet->WeaponHolder = this;
			Bullet->ProxSphere->AddImpulse(GetActorForwardVector() * BulletLaunchImpulse);
		}
		else
			GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Yellow, "Monster: No bullet actor could be spawned, is the bullet overlapping something?");
	}
}


void ALCPPMonster::Resting()
{
	auto Sword = Cast<ALCPPMeleeWeapon>(MeleeWeaponInstance);
	if (Sword != nullptr) Sword->Rest();
}


// Called to bind functionality to input
void ALCPPMonster::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

float ALCPPMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= Damage;
	return 0;
}
