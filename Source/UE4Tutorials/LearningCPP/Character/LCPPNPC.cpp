// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "LCPPNPC.h"
#include "LCPPCharacter.h"
#include <LearningCPP/GUI/LCPPHUD.h>


/*----------------------------------------------------------------
- Initialization -
----------------------------------------------------------------*/

ALCPPNPC::ALCPPNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Proximity Sphere"));
	ProxSphere->AttachTo(RootComponent);
	ProxSphere->SetSphereRadius(500.0f);

	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ALCPPNPC::Prox);
	NpcName = "Give me a name!";
	NpcMessage = "Hi there!";
}


/*----------------------------------------------------------------
- Public functions -
----------------------------------------------------------------*/

void ALCPPNPC::Prox_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ALCPPCharacter>(OtherActor) == nullptr) return;

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		ALCPPHUD* Hud = Cast<ALCPPHUD>(PlayerController->GetHUD());
		Hud->AddMessage(FMessage(NpcName + ": " + NpcMessage, 3.0f, FColor::White, Texture));
	}
}
