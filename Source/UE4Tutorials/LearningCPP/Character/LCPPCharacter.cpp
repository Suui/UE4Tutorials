// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "LCPPCharacter.h"
#include <LearningCPP/ItemPickup/LCPPPickupItem.h>
#include <LearningCPP/GUI/LCPPHUD.h>
#include <LearningCPP/Spells/LCPPSpell.h>


/*----------------------------------------------------------------
- Initialization -
----------------------------------------------------------------*/

ALCPPCharacter::ALCPPCharacter()
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

void ALCPPCharacter::ToggleInventory()
{
	if (GEngine != nullptr && bInventoryIsActive == false)
		GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, "Showing Inventory...");

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	ALCPPHUD* PlayerHud = Cast<ALCPPHUD>(PlayerController->GetHUD());

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
			auto Widget = LCPPWidget(FIcon(NameAndQuantity, Texture));
			Widget.SpellBP = Spells[it->Key];
			PlayerHud->AddWidget(Widget);
		}
	}
}


void ALCPPCharacter::MouseClicked()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	ALCPPHUD* PlayerHud = Cast<ALCPPHUD>(PlayerController->GetHUD());
	PlayerHud->MouseClicked();
}


/*----------------------------------------------------------------
- Public functions -
----------------------------------------------------------------*/

/* Override */
void ALCPPCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	check(InputComponent);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &ALCPPCharacter::ToggleInventory);
	InputComponent->BindAction("MouseClickedLMB", IE_Pressed, this, &ALCPPCharacter::MouseClicked);
	InputComponent->BindAction("MouseClickedRMB", IE_Pressed, this, &ALCPPCharacter::MouseRightClicked);

	InputComponent->BindAxis("Forward", this, &ALCPPCharacter::MoveForward);
	InputComponent->BindAxis("Strafe", this, &ALCPPCharacter::Strafe);
	InputComponent->BindAxis("Yaw", this, &ALCPPCharacter::Yaw);
	InputComponent->BindAxis("Pitch", this, &ALCPPCharacter::Pitch);
}


/* Override */
float ALCPPCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= Damage;
	return Health;
}


void ALCPPCharacter::Pickup(ALCPPPickupItem* Item)
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


void ALCPPCharacter::CastSpell(UClass* SpellBP)
{
	ALCPPSpell* Spell = GetWorld()->SpawnActor<ALCPPSpell>(SpellBP, FVector(0), FRotator(0));

	if (Spell != nullptr)
		Spell->SetCaster(this);
	else
		GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Yellow, "Can't cast " + SpellBP->GetName());
}


void ALCPPCharacter::MouseRightClicked()
{
	if (bInventoryIsActive)
	{
		auto PlayerController = GetWorld()->GetFirstPlayerController();
		auto HUD = Cast<ALCPPHUD>(PlayerController->GetHUD());
		HUD->MouseRightClicked();
	}
}


void ALCPPCharacter::MoveForward(float Amount)
{
	if (Controller != nullptr && Amount != 0)
	{
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, Amount);
	}
}


void ALCPPCharacter::Strafe(float Amount)
{
	if (Controller != nullptr && Amount != 0)
	{
		FVector Right = GetActorRightVector();
		AddMovementInput(Right, Amount);
	}
}


void ALCPPCharacter::Yaw(float Amount)
{
	if (bInventoryIsActive)
	{
		auto PlayerController = GetWorld()->GetFirstPlayerController();
		Cast<ALCPPHUD>(PlayerController->GetHUD())->MouseMoved();
		return;
	}

	if (Controller != nullptr && Amount != 0)
	{
		if (bInvertCameraXAxis) 
			Amount *= -1.0f;
		AddControllerYawInput(CameraSensitivity * Amount * GetWorld()->GetDeltaSeconds());
	}
}


void ALCPPCharacter::Pitch(float Amount)
{
	if (bInventoryIsActive)
	{
		auto PlayerController = GetWorld()->GetFirstPlayerController();
		Cast<ALCPPHUD>(PlayerController->GetHUD())->MouseMoved();
		return;
	}

	if (Controller != nullptr && Amount != 0)
	{
		if (bInvertCameraYAxis) 
			Amount *= -1.0f;
		AddControllerPitchInput(CameraSensitivity * Amount * GetWorld()->GetDeltaSeconds());
	}
}
