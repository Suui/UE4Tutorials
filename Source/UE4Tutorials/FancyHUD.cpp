// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "FancyHUD.h"


void AFancyHUD::DrawHUD()
{
	Super::DrawHUD();

	for (int i = Messages.Num() - 1; i >= 0; i--)
	{
		DrawMessage(Messages[i], i);

		Messages[i].Time -= GetWorld()->GetDeltaSeconds();
		if (Messages[i].Time < 0) Messages.RemoveAt(i);
	}
}


void AFancyHUD::DrawMessage(Message InputMessage, int Index)
{
	float OutputWidth, OutputHeight, Padding = 10.0f;
	GetTextSize(InputMessage.Text, OutputWidth, OutputHeight, HudFont, 1.0f);
	// GetTextSize -- Returns the size of the text, given the FString, in OutputWidth and OutputHeight (Passed by reference)

	float MessageHeight = OutputHeight + 2.0f * Padding;
	float X = 0.0f, Y = Index * MessageHeight;

	DrawRect(FLinearColor::Black, X, Y, Canvas->SizeX, MessageHeight);
	DrawText(InputMessage.Text, InputMessage.Color, X + Padding, Y + Padding, HudFont);
}


void AFancyHUD::AddMessage(Message InputMessage)
{
	Messages.Add(InputMessage);
}