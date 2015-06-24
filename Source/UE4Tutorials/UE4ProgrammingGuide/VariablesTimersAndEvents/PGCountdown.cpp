// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "PGCountdown.h"


/*----------------------------------------------------------------
- Initialization -
----------------------------------------------------------------*/

APGCountdown::APGCountdown()
{
	CountdownText = CreateDefaultSubobject<UTextRenderComponent>("Countdown Number");
	CountdownText->SetHorizontalAlignment(EHTA_Center);
	CountdownText->SetWorldSize(150.f);
	RootComponent = CountdownText;

	CountdownTime = 3;
}


/*----------------------------------------------------------------
- Private functions -
----------------------------------------------------------------*/

void APGCountdown::UpdateTimerDisplay()
{
	CountdownText->SetText(FText::AsNumber(FMath::Max(CountdownTime, 0)));
}


void APGCountdown::AdvanceTimer()
{
	--CountdownTime;
	UpdateTimerDisplay();

	if (CountdownTime < 1)
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		CountdownHasFinished();
	}
}


/*----------------------------------------------------------------
- Protected functions -
----------------------------------------------------------------*/

void APGCountdown::CountdownHasFinished_Implementation()
{
	CountdownText->SetText(FText::FromString("GO!"));
}


/*----------------------------------------------------------------
- Public functions -
----------------------------------------------------------------*/

/* Override */
void APGCountdown::BeginPlay()
{
	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &APGCountdown::AdvanceTimer, 1.0f, true);
}
