// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PGCountdown.generated.h"

UCLASS()
class UE4TUTORIALS_API APGCountdown : public AActor
{
	GENERATED_BODY()

	UTextRenderComponent* CountdownText;
	FTimerHandle CountdownTimerHandle;


public:

	// How long the countdown will run (in seconds)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CountdownTime;


private:

	void UpdateTimerDisplay();

	void AdvanceTimer();


protected:

	UFUNCTION(BlueprintNativeEvent)
	void CountdownHasFinished();
	virtual void CountdownHasFinished_Implementation();


public:

	APGCountdown();

	void BeginPlay() override;
};
