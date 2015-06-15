// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LearningCPPPickupItem.generated.h"


UCLASS()
class UE4TUTORIALS_API ALearningCPPPickupItem : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	UClass* Spell;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
	USphereComponent* ProxSphereComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
	UStaticMeshComponent* StaticMeshComponent;

	ALearningCPPPickupItem();

	UFUNCTION(BlueprintNativeEvent, Category = Collision)
	void Prox(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Prox_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
