// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


struct FIcon
{
	FString Name;
	UTexture2D* Texture;

	FIcon() { Name = "NoName"; Texture = nullptr; }

	FIcon(const FString& Name, UTexture2D* Texture) : Name(Name), Texture(Texture) {}
};


class UE4TUTORIALS_API LearningCPPWidget
{
	FIcon Icon;
	FVector2D Position, Size;

public:

	LearningCPPWidget(FIcon Icon);

	bool Hit(FVector2D ClickPosition);

	float Left();

	float Right();

	float Top();

	float Bottom();

	FIcon GetIcon() const;

	FVector2D GetPosition() const;

	FVector2D GetSize() const;

	void SetIcon(const FIcon& Icon);

	void SetPosition(const FVector2D& Position);

	void SetSize(const FVector2D& Size);

	~LearningCPPWidget();
};
