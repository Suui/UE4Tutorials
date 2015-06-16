// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "LCPPCharacter.generated.h"

class ALCPPPickupItem;


UCLASS()
class UE4TUTORIALS_API ALCPPCharacter : public ACharacter
{
	GENERATED_BODY()

	TMap<FString, int> Backpack;
	TMap<FString, UTexture2D*> ItemIcons;
	TMap<FString, UClass*> Spells;
	bool bInventoryIsActive;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Properties")
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Properties")
	float CameraSensitivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Properties")
	bool bInvertCameraXAxis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Properties")
	float bInvertCameraYAxis;


private:

	void ToggleInventory();

	void MouseClicked();


public:

	ALCPPCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	void Pickup(ALCPPPickupItem* Item);

	void CastSpell(UClass* SpellBP);

	void MouseRightClicked();

	void MoveForward(float Amount);

	void Strafe(float Amount);
	
	void Yaw(float Amount);

	void Pitch(float Amount);
};
