// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "FancyHUD.generated.h"


struct Message
{
	FString Text;
	float Time;
	FColor Color;
	
	Message()
	{
		Time = 5.0f;
		Color = FColor::White;
	}

	Message(FString InputText, float InputTime, FColor InputColor)
	{
		Text = InputText;
		Time = InputTime;
		Color = InputColor;
	}
};


UCLASS()
class UE4TUTORIALS_API AFancyHUD : public AHUD
{
	GENERATED_BODY()
	TArray<Message> Messages;
	
	void DrawMessage(Message InputMessage, int Index);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
	UFont* HudFont;

	virtual void DrawHUD() override;

	void AddMessage(Message InputMessage);
};
