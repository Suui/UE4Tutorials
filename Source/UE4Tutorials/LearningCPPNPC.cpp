// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "LearningCPPNPC.h"
#include "LearningCPPCharacter.h"
#include "LearningCPPHUD.h"


// Sets default values
ALearningCPPNPC::ALearningCPPNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Proximity Sphere"));
	ProxSphere->AttachTo(RootComponent);
	ProxSphere->SetSphereRadius(500.0f);

	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ALearningCPPNPC::Prox);
	NpcName = "Give me a name!";
	NpcMessage = "Hi there!";
}


void ALearningCPPNPC::Prox_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ALearningCPPCharacter>(OtherActor) == nullptr) return;

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		ALearningCPPHUD* Hud = Cast<ALearningCPPHUD>(PlayerController->GetHUD());
		Hud->AddMessage(Message(Texture, NpcName + ": " + NpcMessage, 3.0f, FColor::White));
	}
}


// Called when the game starts or when spawned
void ALearningCPPNPC::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ALearningCPPNPC::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


// Called to bind functionality to input
void ALearningCPPNPC::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

