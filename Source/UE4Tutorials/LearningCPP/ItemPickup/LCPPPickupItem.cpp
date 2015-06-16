// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "LCPPPickupItem.h"
#include <LearningCPP/Character/LCPPCharacter.h>
#include <LearningCPP/GUI/LCPPHUD.h>


/*----------------------------------------------------------------
- Initialization -
----------------------------------------------------------------*/

ALCPPPickupItem::ALCPPPickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProxSphereComponent = CreateDefaultSubobject<USphereComponent>("Proximity Sphere");
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");

	RootComponent = StaticMeshComponent;
	ProxSphereComponent->AttachTo(RootComponent);

	StaticMeshComponent->SetSimulatePhysics(true);
	ProxSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ALCPPPickupItem::Prox);

	Name = "NoName";
	Quantity = 0;
}


/*----------------------------------------------------------------
- Public functions -
----------------------------------------------------------------*/

void ALCPPPickupItem::Prox_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ALCPPCharacter>(OtherActor) == nullptr) return;

	// Reference to the character which is the Player Pawn with index 0 in the World (in this case where we only have 1 offline player).
	ALCPPCharacter* Character = Cast<ALCPPCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	Character->Pickup(this);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	ALCPPHUD* PlayerHUD = Cast<ALCPPHUD>(PlayerController->GetHUD());
	PlayerHUD->AddMessage(FMessage(FString("Picked up ") + FString::FromInt(Quantity) + FString(" " + Name), 5.0f, FColor::White, Icon));

	Destroy();
}
