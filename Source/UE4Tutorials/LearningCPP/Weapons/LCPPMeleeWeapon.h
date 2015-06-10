// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LCPPMeleeWeapon.generated.h"

class ALCPPMonster;


UCLASS()
class UE4TUTORIALS_API ALCPPMeleeWeapon : public AActor
{
	GENERATED_BODY()
	
public:

	TArray<AActor*> TargetsHit;
	ALCPPMonster* WeaponHolder;
	bool bIsSwinging;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeleeWeapon)
	int32 AttackDamage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MeleeWeapon)
	UBoxComponent* WeaponBoxComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MeleeWeapon)
	UStaticMeshComponent* WeaponMesh;


private:

	UFUNCTION()
	void Hit(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:

	// Sets default values for this actor's properties
	ALCPPMeleeWeapon();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void Swing();

	void Rest();
};
