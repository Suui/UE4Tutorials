// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include <LearningCPP/Inventory/LearningCPPWidget.h>
#include "LearningCPPHUD.generated.h"


struct FMessage
{
	FString Text;
	float Time;
	FColor Color;
	UTexture2D* Texture;

	FMessage()
	{
		Time = 5.0f;
		Color = FColor::White;
	}


	FMessage(const FString& Text, float Time, const FColor& Color, UTexture2D* Texture)
		: Text(Text),
		  Time(Time),
		  Color(Color),
		  Texture(Texture) {}
};


UCLASS()
class UE4TUTORIALS_API ALearningCPPHUD : public AHUD
{
	GENERATED_BODY()
	TArray<FMessage> Messages;
	TArray<LearningCPPWidget> Widgets;

	LearningCPPWidget* LastTouchedWidget;

	const float WIDGET_PADDING = 12.0f;
	const float WIDGET_SIZE = 64.0f;
	FVector2D Dimensions;

	void DrawMessage(FMessage Message, int Index);

	void DrawMessages();

	void DrawWidgets();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
	UFont* HudFont;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
	float FontScale = 1.0f;

	virtual void DrawHUD() override;

	void MouseClicked();

	void AddMessage(FMessage Message);

	void AddWidget(LearningCPPWidget Widget);

	void ClearWidgets();
};
