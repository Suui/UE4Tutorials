// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "FancyHUD.generated.h"


struct Message
{
	FString Text;
	float Time;
	FColor Color;
	UTexture2D* Texture;
	
	Message()
	{
		Time = 5.0f;
		Color = FColor::White;
	}

	Message(UTexture2D* InputTexture, FString InputText, float InputTime, FColor InputColor)
	{
		Texture = InputTexture;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
	float FontScale = 1.0f;

	virtual void DrawHUD() override;

	void AddMessage(Message InputMessage);
};
