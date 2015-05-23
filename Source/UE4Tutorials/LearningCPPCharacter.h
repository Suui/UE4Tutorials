// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "LearningCPPCharacter.generated.h"


UCLASS()
class UE4TUTORIALS_API ALearningCPPCharacter : public ACharacter
{
	GENERATED_BODY()

	TMap<FString, int> Backpack;
	TMap<FString, UTexture2D*> ItemIcons;
	bool bInventoryIsActive;

//	void Pickup(APickupItem* Item);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Properties")
	float CameraSensitivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Properties")
	bool bInvertCameraXAxis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Properties")
	float bInvertCameraYAxis;

	// Sets default values for this character's properties
	ALearningCPPCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void MoveForward(float Amount);

	void Strafe(float Amount);

	void Yaw(float Amount);

	void Pitch(float Amount);
};
