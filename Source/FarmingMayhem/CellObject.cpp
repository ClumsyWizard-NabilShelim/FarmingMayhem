// Fill out your copyright notice in the Description page of Project Settings.


#include "CellObject.h"

UCellObject::UCellObject()
{

}

void UCellObject::Init(FVector SetPosition, FIntVector2 SetIndex, bool bSetIsEmpty)
{
	Position = SetPosition;
	Index = SetIndex;
	PlacedActor = PlacedOnCellData(CellHoldingType::None, nullptr);
}

void UCellObject::Used(CellHoldingType Type, AActor* PlaceActor)
{
	PlacedActor.Actor = PlaceActor;
	PlacedActor.HoldingType = Type;
}
