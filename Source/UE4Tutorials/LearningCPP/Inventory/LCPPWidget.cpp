// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Tutorials.h"
#include "LCPPWidget.h"


/*----------------------------------------------------------------
- Initialization -
----------------------------------------------------------------*/

LCPPWidget::LCPPWidget(FIcon Icon): Icon(Icon) {}


/*----------------------------------------------------------------
- Public functions -
----------------------------------------------------------------*/

bool LCPPWidget::Hit(FVector2D ClickPosition)
{
	return ClickPosition.X > Left() && ClickPosition.X < Right() && ClickPosition.Y > Top() && ClickPosition.Y < Bottom();
}


float LCPPWidget::Left() { return Position.X; }


float LCPPWidget::Right() { return Position.X + Size.X; }


float LCPPWidget::Top() { return Position.Y; }


float LCPPWidget::Bottom() { return Position.Y + Size.Y; }


::FIcon LCPPWidget::GetIcon() const { return Icon; }


FVector2D LCPPWidget::GetPosition() const { return Position; }


FVector2D LCPPWidget::GetSize() const { return Size; }


void LCPPWidget::SetIcon(const FIcon& Icon) { this->Icon = Icon; }


void LCPPWidget::SetPosition(const FVector2D& Position) { this->Position = Position; }


void LCPPWidget::SetSize(const FVector2D& Size) { this->Size = Size; }


LCPPWidget::~LCPPWidget() {}
