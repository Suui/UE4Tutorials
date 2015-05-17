// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "NPC.h"
#include "FancyCharacter.h"
#include "FancyHUD.h"


// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Proximity Sphere"));
	ProxSphere->AttachTo(RootComponent);
	ProxSphere->SetSphereRadius(500.0f);

	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::Prox);
	NpcMessage = "Hi there!";
}


void ANPC::Prox_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AFancyCharacter>(OtherActor) == nullptr) return;

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		AFancyHUD* Hud = Cast<AFancyHUD>(PlayerController->GetHUD());
		Hud->AddMessage(Message(NpcMessage, 5.0f, FColor::White));
	}
}


// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ANPC::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

