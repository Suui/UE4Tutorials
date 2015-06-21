// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "PGMyActor.h"


/*----------------------------------------------------------------
- Initialization -
----------------------------------------------------------------*/

APGMyActor::APGMyActor()
{
	TotalDamge = 200;
	DamageTimeInSeconds = 1.f;
}


void APGMyActor::PostInitProperties()
{
	Super::PostInitProperties();

	CalculateValues();
}


/*----------------------------------------------------------------
- Private functions -
----------------------------------------------------------------*/

void APGMyActor::CalculateValues()
{
	DamagePerSecond = TotalDamge / DamageTimeInSeconds;
}


/*----------------------------------------------------------------
- Public functions -
----------------------------------------------------------------*/

#if WITH_EDITOR
/* Override */
void APGMyActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	CalculateValues();
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
