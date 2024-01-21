// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"
#include "CellObject.h"
#include "DrawDebugHelpers.h"
#include "ResourceGenerator.h"

// Sets default values
AGridManager::AGridManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
	Super::BeginPlay();

	CreateGrid();
	UResourceGenerator* ResourceGenerator = GetComponentByClass<UResourceGenerator>();
	if (!ResourceGenerator)
	{
		UE_LOG(LogTemp, Warning, TEXT("No ResourceGenerator"));
		return;
	}

	ResourceGenerator->Initialize(this);
}

void AGridManager::CreateGrid()
{
	Origin = GetActorLocation() - FVector(Length / 2.0f, Width / 2.0f, 0.0f);

	//y represents the value going from left to right while x represents the value going from bottom to top. Its reversed due to unreals different world position matrix calculation

	for (int x = 0; x < GetCellsX(); x++) {
		for (int y = 0; y < GetCellsX(); y++) {

			FVector Position = Origin + FVector(x * GetCellDiameter() + CellRadius, y * GetCellDiameter() + CellRadius, 0.0f);
			FIntVector2 Index = FIntVector2(x, y);

			UCellObject* Cell = NewObject<UCellObject>();
			Cell->Init(Position, Index, true);

			if (x == 0 || y == 0 || x == (GetCellsX() - 1) || y == (GetCellsY() - 1))
			{
				EdgeCells.Add(Cell);
			}

			Grid.Add(Index, Cell);

			if (bShowDebugGizmos)
			{
				DrawDebugBox(GetWorld(), Position, FVector(CellRadius, CellRadius, 2.0f), FColor::Red, true);
			}
		}
	}

	TArray<UCellObject*> UnaccessableCells;
	GetCellsInRange(GetActorLocation(), UnaccessableCenterRadius, UnaccessableCells);
	for (int i = 0; i < UnaccessableCells.Num(); i++)
	{
		UnaccessableCells[i]->Used(CellHoldingType::Occupied, nullptr);
	}
}

UCellObject* AGridManager::GetCell(int X, int Y)
{
	if (X < 0)
		X = 0;
	if (X > GetCellsX() - 1)
		X = GetCellsX() - 1;

	if (Y < 0)
		Y = 0;
	if (Y > GetCellsY() - 1)
		Y = GetCellsY() - 1;

	return Grid[FIntVector2(X, Y)];
}

UCellObject* AGridManager::GetCell(FVector WorldPosition)
{
	int X = FMath::FloorToInt(FMath::Abs(WorldPosition.X - Origin.X) / GetCellDiameter());
	int Y = FMath::FloorToInt(FMath::Abs(WorldPosition.Y - Origin.Y) / GetCellDiameter());

	return GetCell(X, Y);
}

void AGridManager::GetCellsInRange(FVector CentrePosition, int Range, TArray<UCellObject*>& OutCellsInRange)
{
	UCellObject* CentreCell = GetCell(CentrePosition);

	if (CentreCell == nullptr)
		return;

	TArray<UCellObject*> IntermediateCells;
	TArray<UCellObject*> OuterShellCells;
	int StepCount = 0;

	OuterShellCells.Add(CentreCell);

	while (StepCount < Range)
	{
		for (int i = 0; i < OuterShellCells.Num(); i++)
		{
			GetNeightbourCells(OuterShellCells[i], OutCellsInRange, IntermediateCells);
		}

		OuterShellCells = IntermediateCells;
		IntermediateCells.Empty();
		StepCount++;
	}
}

void AGridManager::GetNeightbourCells(UCellObject* CentreCell, TArray<UCellObject*>& OutCellsInRange, TArray<UCellObject*>& OutIntermediateCells)
{
	for (int x = -1; x <= 1; x++)
	{
		if (x == 0)
			continue;

		ProcessNeightbourCell(CentreCell, x, 0, OutCellsInRange, OutIntermediateCells);
	}
	for (int y = -1; y <= 1; y++)
	{
		if (y == 0)
			continue;

		ProcessNeightbourCell(CentreCell, 0, y, OutCellsInRange, OutIntermediateCells);
	}
}

void AGridManager::ProcessNeightbourCell(UCellObject* CentreCell, int X, int Y, TArray<UCellObject*>& OutCellsInRange, TArray<UCellObject*>& OutIntermediateCells)
{
	int NeightbourX = CentreCell->Index.X + X;
	int NeightbourY = CentreCell->Index.Y + Y;
	UCellObject* NeighbourCell = GetCell(NeightbourX, NeightbourY);

	if (NeighbourCell == nullptr || OutCellsInRange.Contains(NeighbourCell))
		return;

	OutCellsInRange.Add(NeighbourCell);
	OutIntermediateCells.Add(NeighbourCell);
}