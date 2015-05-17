// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "NPC.generated.h"


UCLASS()
class UE4TUTORIALS_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	class USphereComponent* ProxSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Properties")
	UTexture2D* Texture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Properties")
	FString NpcName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Properties")
	FString NpcMessage;

	// Sets default values for this character's properties
	ANPC();

	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void Prox(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Prox_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
};
