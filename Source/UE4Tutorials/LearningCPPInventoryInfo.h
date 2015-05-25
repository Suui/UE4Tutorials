// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4Tutorials.h"


struct Icon
{
	FString Name;
	UTexture2D* Texture;

	Icon() { Name = "NoName"; Texture = nullptr; }

	Icon(const FString& InputName, UTexture2D* InputTexture) : Name(InputName), Texture(InputTexture) {}
};


struct Widget
{
	Icon Icon;
	FVector2D Position, Size;

	Widget(::Icon Icon) : Icon(Icon) {}

	bool Hit(FVector2D ClickPosition)
	{
		return ClickPosition.X > Left() && ClickPosition.X < Right() && ClickPosition.Y > Top() && ClickPosition.Y < Bottom();
	}

	float Left() { return Position.X; }

	float Right() { return Position.X + Size.X; }

	float Top() { return Position.Y; }

	float Bottom() { return Position.X + Size.Y; }
};

