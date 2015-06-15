// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "LearningCPPCharacter.h"
#include <UE4Tutorials/LearningCPP/ItemPickup/LearningCPPPickupItem.h>
#include <UE4Tutorials/LearningCPP/GUI/LearningCPPHUD.h>
#include <UE4Tutorials/LearningCPP/Spells/LCPPSpell.h>


/*----------------------------------------------------------------
- Initialization -
----------------------------------------------------------------*/

ALearningCPPCharacter::ALearningCPPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 200;
	CameraSensitivity = 120.0f;
	bInvertCameraXAxis = false;
	bInvertCameraYAxis = true;
	bInventoryIsActive = false;
}


/*----------------------------------------------------------------
- Private functions -
----------------------------------------------------------------*/

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
			auto Widget = LearningCPPWidget(FIcon(NameAndQuantity, Texture));
			Widget.SpellBP = Spells[it->Key];
			PlayerHud->AddWidget(Widget);
		}
	}
}


void ALearningCPPCharacter::MouseClicked()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	ALearningCPPHUD* PlayerHud = Cast<ALearningCPPHUD>(PlayerController->GetHUD());
	PlayerHud->MouseClicked();
}


/*----------------------------------------------------------------
- Public functions -
----------------------------------------------------------------*/

/* Override */
void ALearningCPPCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	check(InputComponent);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &ALearningCPPCharacter::ToggleInventory);
	InputComponent->BindAction("MouseClickedLMB", IE_Pressed, this, &ALearningCPPCharacter::MouseClicked);
	InputComponent->BindAction("MouseClickedRMB", IE_Pressed, this, &ALearningCPPCharacter::MouseRightClicked);

	InputComponent->BindAxis("Forward", this, &ALearningCPPCharacter::MoveForward);
	InputComponent->BindAxis("Strafe", this, &ALearningCPPCharacter::Strafe);
	InputComponent->BindAxis("Yaw", this, &ALearningCPPCharacter::Yaw);
	InputComponent->BindAxis("Pitch", this, &ALearningCPPCharacter::Pitch);
}


/* Override */
float ALearningCPPCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= Damage;
	return Health;
}


void ALearningCPPCharacter::Pickup(ALearningCPPPickupItem* Item)
{
	if (Backpack.Find(Item->Name))
		Backpack[Item->Name] += Item->Quantity;
	else
	{
		Backpack.Add(Item->Name, Item->Quantity);
		ItemIcons.Add(Item->Name, Item->Icon);
		Spells.Add(Item->Name, Item->Spell);
	}
}


void ALearningCPPCharacter::CastSpell(UClass* SpellBP)
{
	ALCPPSpell* Spell = GetWorld()->SpawnActor<ALCPPSpell>(SpellBP, FVector(0), FRotator(0));

	if (Spell != nullptr)
		Spell->SetCaster(this);
	else
		GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Yellow, "Can't cast " + SpellBP->GetName());
}


void ALearningCPPCharacter::MouseRightClicked()
{
	if (bInventoryIsActive)
	{
		auto PlayerController = GetWorld()->GetFirstPlayerController();
		auto HUD = Cast<ALearningCPPHUD>(PlayerController->GetHUD());
		HUD->MouseRightClicked();
	}
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
