// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridManager.generated.h"

UCLASS()
class FARMINGMAYHEM_API AGridManager : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	int Width = 5000;
	UPROPERTY(EditAnywhere)
	int Length = 5000;
	UPROPERTY(EditAnywhere)
	int CellRadius = 100;
	UPROPERTY(EditAnywhere)
	int UnaccessableCenterRadius = 5;
	UPROPERTY(EditAnywhere)
	bool bShowDebugGizmos = true;


	FVector Origin = FVector::ZeroVector;
	UPROPERTY()
	TMap<FIntVector2, class UCellObject*> Grid;
	UPROPERTY()
	TArray<UCellObject*> EdgeCells;

private:
	void CreateGrid();
	void GetNeightbourCells(UCellObject* CentreCell, TArray<UCellObject*>& OutCellsInRange, TArray<UCellObject*>& OutIntermediateCells);
	void ProcessNeightbourCell(UCellObject* CentreCell, int X, int Y, TArray<UCellObject*>& OutCellsInRange, TArray<UCellObject*>& OutIntermediateCells);

protected:
	virtual void BeginPlay() override;

public:
	AGridManager();
	UCellObject* GetCell(int X, int Y);
	UCellObject* GetCell(FVector AtPosition);
	const TMap<FIntVector2, UCellObject*> GetGrid()
	{
		return Grid;
	}
	void GetCellsInRange(FVector CentrePosition, int Range, TArray<UCellObject*>& OutCellsInRange);

	inline const int GetCellDiameter() const { return CellRadius * 2; }
	inline const int GetCellsX() const { return Length / GetCellDiameter(); }
	inline const int GetCellsY() const { return Width / GetCellDiameter(); }
	const TArray<UCellObject*> GetEdgeCells() { return EdgeCells; }
};
