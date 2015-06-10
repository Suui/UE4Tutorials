// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "LCPPMonster.generated.h"

UCLASS()
class UE4TUTORIALS_API ALCPPMonster : public ACharacter
{
	GENERATED_BODY()

	bool bEnemyInSight;


public:

	AActor* MeleeWeaponInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	int32 ExperienceDrop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	UClass* Loot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	int32 BaseAttackDMG;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float BaseAttackCD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	UClass* MeleeWeaponBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	UClass* BulletBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float BulletLaunchImpulse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	bool EnableAttackAnim;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MonsterProperties)
	bool bEnemyInAttackRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MonsterProperties)
	float TimeSinceLastBaseAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MonsterProperties)
	USphereComponent* SightSphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MonsterProperties)
	USphereComponent* BaseAttackRangeSphereComp;


private:

	UFUNCTION()
	void StartChasing(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void StopChasing(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	UFUNCTION()
	void StartAttacking(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void StopAttacking(AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	void ChasePlayer(float DeltaTime);

public:

	UFUNCTION(BlueprintCallable, Category = MonsterFunctions)
	void SwordSwung();

	UFUNCTION(BlueprintCallable, Category = MonsterFunctions)
	void Resting();

	// Sets default values for this character's properties
	ALCPPMonster();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
};
