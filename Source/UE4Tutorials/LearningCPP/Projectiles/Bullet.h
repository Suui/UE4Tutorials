// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class UE4TUTORIALS_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BulletProperties)
	int32 Damage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = BulletProperties)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = BulletProperties)
	USphereComponent* ProxSphere;

	UFUNCTION(BlueprintNativeEvent, Category = BulletFunctions)
	void Prox(AActor* OtherAction, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSwpp, const FHitResult& SweepResult);

	virtual void Prox_Implementation(AActor* OtherAction, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSwpp, const FHitResult& SweepResult);


	// Sets default values for this actor's properties
	ABullet();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
