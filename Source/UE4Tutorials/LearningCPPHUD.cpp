// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "LearningCPPHUD.h"
#include "LearningCPPInventoryInfo.h"


void ALearningCPPHUD::DrawHUD()
{
	Super::DrawHUD();

	Dimensions.X = Canvas->SizeX;
	Dimensions.Y = Canvas->SizeY;

	DrawMessages();
	DrawWidgets();
}


void ALearningCPPHUD::DrawMessages()
{
	for (int i = Messages.Num() - 1; i >= 0; i--)
	{
		DrawMessage(Messages[i], i);

		Messages[i].Time -= GetWorld()->GetDeltaSeconds();
		if (Messages[i].Time < 0) Messages.RemoveAt(i);
	}
}


void ALearningCPPHUD::DrawMessage(Message InputMessage, int Index)
{
	float OutputWidth, OutputHeight, Padding = 10.0f;
	GetTextSize(InputMessage.Text, OutputWidth, OutputHeight, HudFont, FontScale);
	// GetTextSize -- Returns the size of the text, given the FString, in OutputWidth and OutputHeight (Passed by reference)

	float MessageHeight = OutputHeight + 2.0f * Padding;
	float X = 0.0f, Y = Index * MessageHeight;

	DrawRect(FLinearColor::Black, X, Y, Dimensions.X, MessageHeight);
	if (InputMessage.Texture != nullptr)
		DrawTexture(InputMessage.Texture, X, Y, MessageHeight, MessageHeight, 0, 0, 1, 1);
	DrawText(InputMessage.Text, InputMessage.Color, X + Padding + MessageHeight, Y + Padding, HudFont, FontScale);
}


void ALearningCPPHUD::DrawWidgets()
{
	for (int i = 0; i < Widgets.Num(); ++i)
	{
		DrawTexture(Widgets[i].Icon.Texture, Widgets[i].Position.X, Widgets[i].Position.Y, Widgets[i].Size.X, Widgets[i].Size.Y, 0, 0, 1, 1);
		DrawText(Widgets[i].Icon.Name, FLinearColor::Yellow, Widgets[i].Position.X, Widgets[i].Position.Y, HudFont, 0.6f);
	}
}


void ALearningCPPHUD::AddMessage(Message InputMessage)
{
	Messages.Add(InputMessage);
}


void ALearningCPPHUD::AddWidget(Widget Widget)
{
	// Find the position of the widget based on the grid.
	FVector2D Start(200, 200), Padding(12, 12);
	Widget.Size = FVector2D(100, 100);
	Widget.Position = Start;

	for (int i = 0; i < Widgets.Num(); ++i)
	{
		Widget.Position.X += Widget.Position.X + Padding.X;
		// If there is no more room to the right then jump to the next line.
		if (Widget.Position.X + Widget.Size.X > Dimensions.X)
		{
			Widget.Position.X = Start.X;
			Widget.Position.Y = Widget.Size.Y + Padding.Y;
		}
	}

	Widgets.Add(Widget);
}


void ALearningCPPHUD::ClearWidgets()
{

}