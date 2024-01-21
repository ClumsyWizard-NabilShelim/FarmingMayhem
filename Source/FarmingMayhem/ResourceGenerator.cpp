#include "ResourceGenerator.h"
#include "GridManager.h"
#include "CellObject.h"
#include "Kismet/GameplayStatics.h"
#include "Resource.h"

UResourceGenerator::UResourceGenerator()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UResourceGenerator::Initialize(AGridManager* SetGridManager)
{
	GridManager = SetGridManager;

	UCellObject* CentreCell = GridManager->GetCell(GridManager->GetCellsX() / 2, GridManager->GetCellsY() / 2);
	GridManager->GetCellsInRange(CentreCell->Position, KeepEmptyCellsRadius, KeepEmptyCells);

	GenerateResource(ChanceToSpawnPerTile);
}

void UResourceGenerator::BeginPlay()
{
	Super::BeginPlay();
	CurrentRegenerationTime = FMath::RandRange(MinRegenerationDelay, MaxRegenerationDelay);
}

void UResourceGenerator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentRegenerationTime <= 0)
	{
		GenerateResource(ChanceToReSpawnPerTile);
		CurrentRegenerationTime = FMath::RandRange(MinRegenerationDelay, MaxRegenerationDelay);
	}
	else
	{
		CurrentRegenerationTime -= DeltaTime;
	}
}

//Helper functions

void UResourceGenerator::GenerateResource(float SpawnChance)
{
	if (Resources.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No Resources"));
		return;
	}

	for (const TPair<FIntVector2, UCellObject*>& CellPair : GridManager->GetGrid())
	{
		if (KeepEmptyCells.Contains(CellPair.Value) || !CellPair.Value->IsEmpty())
			continue;

		TSubclassOf<AResource>& ActorToPlace = Resources[FMath::RandRange(0, Resources.Num() - 1)];

		int RandomRoll = FMath::RandRange(0, 100);

		if (RandomRoll > SpawnChance)
			continue;

		AResource* Resource = Cast<AResource>(GetWorld()->SpawnActor(ActorToPlace));
		Resource->Initialize(CellPair.Value);
		Resource->SetActorLocation(CellPair.Value->Position);
	}
}