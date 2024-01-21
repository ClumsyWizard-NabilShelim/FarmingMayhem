// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CellObject.generated.h"

enum CellHoldingType
{
	None = -1,
	PlowedGround,
	Resource,
	Plant,
	Occupied
};

struct PlacedOnCellData
{
	CellHoldingType HoldingType;
	AActor* Actor;

	PlacedOnCellData(){}
	PlacedOnCellData(CellHoldingType Type, AActor* SetActor)
	{
		HoldingType = Type;
		Actor = SetActor;
	}
};

UCLASS()
class FARMINGMAYHEM_API UCellObject : public UObject
{
	GENERATED_BODY()

private:
	PlacedOnCellData PlacedActor;

public:
	FVector Position;
	FIntVector2 Index;

public:
	UCellObject();
	void Init(FVector SetPosition, FIntVector2 SetIndex, bool bSetIsEmpty);

	void Used(CellHoldingType Type, AActor* PlaceActor);

	bool IsEmpty() { return PlacedActor.HoldingType != CellHoldingType::Occupied && PlacedActor.Actor == nullptr; }

	AActor* GetPlacedActor() { return PlacedActor.Actor; }
	
	bool HasPlacedActor(CellHoldingType Type) { return PlacedActor.HoldingType == Type; }
	template<typename T>
	T* GetPlacedActor(CellHoldingType Type)
	{
		if (PlacedActor.HoldingType != Type)
			return nullptr;

		return Cast<T>(PlacedActor.Actor);
	}
};