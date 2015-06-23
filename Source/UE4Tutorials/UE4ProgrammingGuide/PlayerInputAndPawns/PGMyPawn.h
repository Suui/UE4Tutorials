// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "PGMyPawn.generated.h"


UCLASS()
class UE4TUTORIALS_API APGMyPawn : public APawn
{
	GENERATED_BODY()

	FVector ForwardVelocity;
	FVector StrafeVelocity;
	bool bIsGrowing;


public:

	UPROPERTY(VisibleAnywhere, Category = MyPawnProperties)
	USceneComponent* OurVisibleComponent;

	UPROPERTY(VisibleAnywhere, Category = MyPawnProperties)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = MyPawnProperties)
	UCameraComponent* OurCamera;

	UPROPERTY(EditAnywhere, Category = MyPawnProperties)
	float MovementSpeed;


private:

	void MoveForward(float AxisValue);

	void Strafe(float AxisValue);

	void StartGrowing();

	void StopGrowing();


public:

	APGMyPawn();

	void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	void Tick(float DeltaTime) override;
};
