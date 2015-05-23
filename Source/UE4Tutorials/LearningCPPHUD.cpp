// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "LearningCPPHUD.h"


void ALearningCPPHUD::DrawHUD()
{
	Super::DrawHUD();

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

	DrawRect(FLinearColor::Black, X, Y, Canvas->SizeX, MessageHeight);
	if (InputMessage.Texture != nullptr)
		DrawTexture(InputMessage.Texture, X, Y, MessageHeight, MessageHeight, 0, 0, 1, 1);
	DrawText(InputMessage.Text, InputMessage.Color, X + Padding + MessageHeight, Y + Padding, HudFont, FontScale);
}


void ALearningCPPHUD::AddMessage(Message InputMessage)
{
	Messages.Add(InputMessage);
}