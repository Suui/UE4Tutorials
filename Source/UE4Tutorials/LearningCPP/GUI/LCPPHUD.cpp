// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "LCPPHUD.h"
#include <LearningCPP/Character/LCPPCharacter.h>


/*----------------------------------------------------------------
- Private functions -
----------------------------------------------------------------*/

void ALCPPHUD::DrawMessages()
{
	for (int i = Messages.Num() - 1; i >= 0; i--)
	{
		DrawMessage(Messages[i], i);

		Messages[i].Time -= GetWorld()->GetDeltaSeconds();
		if (Messages[i].Time < 0) Messages.RemoveAt(i);
	}
}


void ALCPPHUD::DrawWidgets()
{
	for (int i = 0; i < Widgets.Num(); ++i)
	{
		DrawTexture(Widgets[i].GetIcon().Texture, Widgets[i].GetPosition().X, Widgets[i].GetPosition().Y, Widgets[i].GetSize().X, Widgets[i].GetSize().Y, 0, 0, 1, 1);
		DrawText(Widgets[i].GetIcon().Name, FLinearColor::Yellow, Widgets[i].GetPosition().X, Widgets[i].GetPosition().Y, HudFont, 0.6f);
	}
}


void ALCPPHUD::DrawMessage(FMessage Message, int Index)
{
	float OutputWidth, OutputHeight, Padding = 10.0f;
	GetTextSize(Message.Text, OutputWidth, OutputHeight, HudFont, FontScale);
	// GetTextSize -- Returns the size of the text, given the FString, in OutputWidth and OutputHeight (Passed by reference)

	float MessageHeight = OutputHeight + 2.0f * Padding;
	float X = 0.0f, Y = Index * MessageHeight;

	DrawRect(FLinearColor::Black, X, Y, Dimensions.X, MessageHeight);
	if (Message.Texture != nullptr)
		DrawTexture(Message.Texture, X, Y, MessageHeight, MessageHeight, 0, 0, 1, 1);
	DrawText(Message.Text, Message.Color, X + Padding + MessageHeight, Y + Padding, HudFont, FontScale);
}


/*----------------------------------------------------------------
- Public functions -
----------------------------------------------------------------*/

/* Override */
void ALCPPHUD::DrawHUD()
{
	Super::DrawHUD();

	Dimensions.X = Canvas->SizeX;
	Dimensions.Y = Canvas->SizeY;

	DrawMessages();
	DrawWidgets();
}


void ALCPPHUD::MouseClicked()
{
	FVector2D ClickPosition;
	PlayerOwner->GetMousePosition(ClickPosition.X, ClickPosition.Y);
	LastTouchedWidget = nullptr;

	for (int i = 0; i < Widgets.Num(); i++)
	{
		if (Widgets[i].Hit(ClickPosition))
		{
			LastTouchedWidget = &Widgets[i];
			if (GEngine) GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Yellow, LastTouchedWidget->GetIcon().Name + " has been clicked!");
			return;
		}
	}
}


void ALCPPHUD::MouseRightClicked()
{
	FVector2D MousePos;
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->GetMousePosition(MousePos.X, MousePos.Y);

	for (int i = 0; i < Widgets.Num(); ++i)
	{
		if (Widgets[i].Hit(MousePos))
		{
			auto Character = Cast<ALCPPCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (Character != nullptr && Widgets[i].SpellBP != nullptr) Character->CastSpell(Widgets[i].SpellBP);
		}
	}
}


void ALCPPHUD::MouseMoved()
{
	FVector2D CurrentMousePos, MousePosDifference;

	PlayerOwner->GetMousePosition(CurrentMousePos.X, CurrentMousePos.Y);
	MousePosDifference = CurrentMousePos - LastMousePos;

	float DragTime = PlayerOwner->GetInputKeyTimeDown(EKeys::LeftMouseButton);
	if (DragTime > 0.0f && LastTouchedWidget != nullptr)
		LastTouchedWidget->SetPosition(LastTouchedWidget->GetPosition() + MousePosDifference);

	LastMousePos = CurrentMousePos;
}


void ALCPPHUD::AddMessage(FMessage InputMessage)
{
	Messages.Add(InputMessage);
}


void ALCPPHUD::AddWidget(LCPPWidget Widget)
{
	Widget.SetSize(FVector2D(WIDGET_SIZE, WIDGET_SIZE));

	if (Widgets.Num() == 0)
		Widget.SetPosition(FVector2D(WIDGET_PADDING, 200));
	else
		Widget.SetPosition(FVector2D(Widgets[Widgets.Num() - 1].GetPosition().X + WIDGET_SIZE + WIDGET_PADDING, 
									 Widgets[Widgets.Num() - 1].GetPosition().Y));

	if (Widget.GetPosition().X > Dimensions.X)
		Widget.SetPosition(FVector2D(WIDGET_PADDING, 
									 Widgets[Widgets.Num() - 1].GetPosition().Y + WIDGET_PADDING));

	Widgets.Add(Widget);
}


void ALCPPHUD::ClearWidgets()
{
	Widgets.Empty();
}
