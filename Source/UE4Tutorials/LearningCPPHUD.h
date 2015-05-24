// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "LearningCPPInventoryInfo.h"
#include "LearningCPPHUD.generated.h"


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
class UE4TUTORIALS_API ALearningCPPHUD : public AHUD
{
	GENERATED_BODY()
	TArray<Message> Messages;
	TArray<Widget> Widgets;

	const float WIDGET_PADDING = 12.0f;
	const float WIDGET_SIZE = 64.0f;
	FVector2D Dimensions;

	void DrawMessage(Message InputMessage, int Index);

	void DrawMessages();

	void DrawWidgets();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
	UFont* HudFont;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
	float FontScale = 1.0f;

	virtual void DrawHUD() override;

	void AddMessage(Message InputMessage);

	void AddWidget(Widget Widget);

	void ClearWidgets();
};
