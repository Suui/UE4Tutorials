// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "LearningCPPWidget.h"


/*----------------------------------------------------------------
- Initialization -
----------------------------------------------------------------*/

LearningCPPWidget::LearningCPPWidget(FIcon Icon): Icon(Icon) {}


/*----------------------------------------------------------------
- Public functions -
----------------------------------------------------------------*/

bool LearningCPPWidget::Hit(FVector2D ClickPosition)
{
	return ClickPosition.X > Left() && ClickPosition.X < Right() && ClickPosition.Y > Top() && ClickPosition.Y < Bottom();
}


float LearningCPPWidget::Left() { return Position.X; }


float LearningCPPWidget::Right() { return Position.X + Size.X; }


float LearningCPPWidget::Top() { return Position.Y; }


float LearningCPPWidget::Bottom() { return Position.Y + Size.Y; }


::FIcon LearningCPPWidget::GetIcon() const { return Icon; }


FVector2D LearningCPPWidget::GetPosition() const { return Position; }


FVector2D LearningCPPWidget::GetSize() const { return Size; }


void LearningCPPWidget::SetIcon(const FIcon& Icon) { this->Icon = Icon; }


void LearningCPPWidget::SetPosition(const FVector2D& Position) { this->Position = Position; }


void LearningCPPWidget::SetSize(const FVector2D& Size) { this->Size = Size; }


LearningCPPWidget::~LearningCPPWidget() {}
