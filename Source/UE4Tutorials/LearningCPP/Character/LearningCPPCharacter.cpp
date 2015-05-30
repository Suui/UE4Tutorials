// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "LearningCPPCharacter.h"
#include <LearningCPP/ItemPickup/LearningCPPPickupItem.h>
#include <LearningCPP/GUI/LearningCPPHUD.h>


// Sets default values
ALearningCPPCharacter::ALearningCPPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraSensitivity = 120.0f;
	bInvertCameraXAxis = false;
	bInvertCameraYAxis = true;
	bInventoryIsActive = false;
}


// Called when the game starts or when spawned
void ALearningCPPCharacter::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ALearningCPPCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}


// Called to bind functionality to input
void ALearningCPPCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	check(InputComponent);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &ALearningCPPCharacter::ToggleInventory);
	InputComponent->BindAction("MouseClickedLMB", IE_Pressed, this, &ALearningCPPCharacter::MouseClicked);

	InputComponent->BindAxis("Forward", this, &ALearningCPPCharacter::MoveForward);
	InputComponent->BindAxis("Strafe", this, &ALearningCPPCharacter::Strafe);
	InputComponent->BindAxis("Yaw", this, &ALearningCPPCharacter::Yaw);
	InputComponent->BindAxis("Pitch", this, &ALearningCPPCharacter::Pitch);
}


void ALearningCPPCharacter::Pickup(ALearningCPPPickupItem* Item)
{
	if (Backpack.Find(Item->Name))
		Backpack[Item->Name] += Item->Quantity;
	else
	{
		Backpack.Add(Item->Name, Item->Quantity);
		ItemIcons.Add(Item->Name, Item->Icon);
	}
}


void ALearningCPPCharacter::ToggleInventory()
{
	if (GEngine != nullptr && bInventoryIsActive == false)
		GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, "Showing Inventory...");

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	ALearningCPPHUD* PlayerHud = Cast<ALearningCPPHUD>(PlayerController->GetHUD());

	if (bInventoryIsActive)
	{
		PlayerHud->ClearWidgets();
		bInventoryIsActive = false;
		PlayerController->bShowMouseCursor = false;
		return;
	}

	bInventoryIsActive = true;
	PlayerController->bShowMouseCursor = true;

	for (TMap<FString, int>::TIterator it = Backpack.CreateIterator(); it; ++it)
	{
		FString NameAndQuantity = it->Key + FString::Printf(TEXT("x%d"), it->Value);
		if (ItemIcons.Find(it->Key))
		{
			UTexture2D* Texture = ItemIcons[it->Key];
			PlayerHud->AddWidget(LearningCPPWidget(FIcon(NameAndQuantity, Texture)));
		}
	}
}


void ALearningCPPCharacter::MouseClicked()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	ALearningCPPHUD* PlayerHud = Cast<ALearningCPPHUD>(PlayerController->GetHUD());
	PlayerHud->MouseClicked();
}


void ALearningCPPCharacter::MoveForward(float Amount)
{
	if (Controller != nullptr && Amount != 0)
	{
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, Amount);
	}
}


void ALearningCPPCharacter::Strafe(float Amount)
{
	if (Controller != nullptr && Amount != 0)
	{
		FVector Right = GetActorRightVector();
		AddMovementInput(Right, Amount);
	}
}


void ALearningCPPCharacter::Yaw(float Amount)
{
	if (bInventoryIsActive)
	{
		auto PlayerController = GetWorld()->GetFirstPlayerController();
		Cast<ALearningCPPHUD>(PlayerController->GetHUD())->MouseMoved();
		return;
	}

	if (Controller != nullptr && Amount != 0)
	{
		if (bInvertCameraXAxis) 
			Amount *= -1.0f;
		AddControllerYawInput(CameraSensitivity * Amount * GetWorld()->GetDeltaSeconds());
	}
}


void ALearningCPPCharacter::Pitch(float Amount)
{
	if (bInventoryIsActive)
	{
		auto PlayerController = GetWorld()->GetFirstPlayerController();
		Cast<ALearningCPPHUD>(PlayerController->GetHUD())->MouseMoved();
		return;
	}

	if (Controller != nullptr && Amount != 0)
	{
		if (bInvertCameraYAxis) 
			Amount *= -1.0f;
		AddControllerPitchInput(CameraSensitivity * Amount * GetWorld()->GetDeltaSeconds());
	}
}
