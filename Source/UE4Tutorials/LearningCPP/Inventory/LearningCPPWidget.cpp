// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "LearningCPPWidget.h"


LearningCPPWidget::LearningCPPWidget(::Icon Icon): Icon(Icon) {}


bool LearningCPPWidget::Hit(FVector2D ClickPosition)
{
	return ClickPosition.X > Left() && ClickPosition.X < Right() && ClickPosition.Y > Top() && ClickPosition.Y < Bottom();
}


float LearningCPPWidget::Left() { return Position.X; }


float LearningCPPWidget::Right() { return Position.X + Size.X; }


float LearningCPPWidget::Top() { return Position.Y; }


float LearningCPPWidget::Bottom() { return Position.Y + Size.Y; }


::Icon LearningCPPWidget::GetIcon() const { return Icon; }


FVector2D LearningCPPWidget::GetPosition() const { return Position; }


FVector2D LearningCPPWidget::GetSize() const { return Size; }


void LearningCPPWidget::SetIcon(const ::Icon& InputIcon) { Icon = InputIcon; }


void LearningCPPWidget::SetPosition(const FVector2D& InputPosition) { Position = InputPosition; }


void LearningCPPWidget::SetSize(const FVector2D& InputSize) { Size = InputSize; }


LearningCPPWidget::~LearningCPPWidget() {}

