// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


struct Icon
{
	FString Name;
	UTexture2D* Texture;

	Icon() { Name = "NoName"; Texture = nullptr; }

	Icon(const FString& InputName, UTexture2D* InputTexture) : Name(InputName), Texture(InputTexture) {}
};


class UE4TUTORIALS_API LearningCPPWidget
{
	Icon Icon;
	FVector2D Position, Size;

public:

	LearningCPPWidget(::Icon Icon);

	bool Hit(FVector2D ClickPosition);

	float Left();

	float Right();

	float Top();

	float Bottom();

	::Icon GetIcon() const;

	FVector2D GetPosition() const;

	FVector2D GetSize() const;

	void SetIcon(const ::Icon& InputIcon);

	void SetPosition(const FVector2D& InputPosition);

	void SetSize(const FVector2D& InputSize);

	~LearningCPPWidget();
};
