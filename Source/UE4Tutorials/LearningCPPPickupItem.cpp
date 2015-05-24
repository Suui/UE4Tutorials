// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "LearningCPPPickupItem.h"
#include "LearningCPPCharacter.h"
#include "LearningCPPHUD.h"


// Sets default values
ALearningCPPPickupItem::ALearningCPPPickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProxSphereComponent = CreateDefaultSubobject<USphereComponent>("Proximity Sphere");
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");

	RootComponent = StaticMeshComponent;
	ProxSphereComponent->AttachTo(RootComponent);

	StaticMeshComponent->SetSimulatePhysics(true);
	ProxSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ALearningCPPPickupItem::Prox);

	Name = "NoName";
	Quantity = 0;
}


void ALearningCPPPickupItem::Prox_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ALearningCPPCharacter>(OtherActor) == nullptr) return;

	// Reference to the character which is the Player Pawn with index 0 in the World (in this case where we only have 1 offline player).
	ALearningCPPCharacter* Character = Cast<ALearningCPPCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	Character->Pickup(this);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	ALearningCPPHUD* PlayerHUD = Cast<ALearningCPPHUD>(PlayerController->GetHUD());
	PlayerHUD->AddMessage(Message(Icon, FString("Picked up ") + FString::FromInt(Quantity) + FString(" " + Name), 5.0f, FColor::White));

	Destroy();
}


// Called when the game starts or when spawned
void ALearningCPPPickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ALearningCPPPickupItem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

