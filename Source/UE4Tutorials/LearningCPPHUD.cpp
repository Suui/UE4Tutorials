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


void ALearningCPPHUD::MouseClicked()
{
	FVector2D ClickPosition;
	PlayerOwner->GetMousePosition(ClickPosition.X, ClickPosition.Y);
	LastTouchesWidget = nullptr;

	for (int i = 0; i < Widgets.Num(); i++)
	{
		if (Widgets[i].Hit(ClickPosition))
		{
			LastTouchesWidget = &Widgets[i];
			if (GEngine) GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Yellow, LastTouchesWidget->Icon.Name + "has been clicked!");
			return;
		}
	}
}



void ALearningCPPHUD::AddMessage(Message InputMessage)
{
	Messages.Add(InputMessage);
}


void ALearningCPPHUD::AddWidget(Widget Widget)
{
	Widget.Size = FVector2D(WIDGET_SIZE, WIDGET_SIZE);

	if (Widgets.Num() == 0)
		Widget.Position = FVector2D(WIDGET_PADDING, 200);
	else
	{
		Widget.Position.X = Widgets[Widgets.Num() - 1].Position.X + WIDGET_SIZE + WIDGET_PADDING;
		Widget.Position.Y = Widgets[Widgets.Num() - 1].Position.Y;
	}

	if (Widget.Position.X > Dimensions.X)
	{
		Widget.Position.X = WIDGET_PADDING;
		Widget.Position.Y = Widgets[Widgets.Num() - 1].Position.Y + WIDGET_PADDING;
	}

	Widgets.Add(Widget);
}


void ALearningCPPHUD::ClearWidgets()
{
	Widgets.Empty();
}