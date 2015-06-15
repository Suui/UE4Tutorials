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
	float Health;

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

	ALCPPMonster();

	void PostInitializeComponents() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = MonsterFunctions)
	void Attack();

	UFUNCTION(BlueprintCallable, Category = MonsterFunctions)
	void Resting();

	float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
