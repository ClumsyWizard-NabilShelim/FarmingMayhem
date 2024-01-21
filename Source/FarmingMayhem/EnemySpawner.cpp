// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Kismet/GameplayStatics.h"
#include "FarmingPlayerController.h"
#include "CellObject.h"
#include "DayNightSystem.h"
#include "FarmingMayhemGameMode.h"
#include "EnemyAI.h"
#include "GridManager.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	AFarmingMayhemGameMode* GameMode = Cast<AFarmingMayhemGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GridManager = GameMode->GetGridManager();
	DayNightSystem = GameMode->GetDayNightSystem();

	CurrentDaysBetweenSpawn = FMath::RandRange(MinDaysBetweenSpawn, MaxDaysBetweenSpawn) * DayNightSystem->GetSecondsPerDay();
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentSpawnTime >= CurrentDaysBetweenSpawn)
	{
		CurrentDaysBetweenSpawn = FMath::RandRange(MinDaysBetweenSpawn, MaxDaysBetweenSpawn) * DayNightSystem->GetSecondsPerDay();
		CurrentSpawnTime = 0.0f;
		SpawnEnemies();
	}
	else
	{
		CurrentSpawnTime += DeltaTime * DayNightSystem->GetTimeElapseSpeed();
	}
}

void AEnemySpawner::SpawnEnemies()
{
	for (UCellObject* Cell : GridManager->GetEdgeCells())
	{
		float Chance = FMath::RandRange(0, 100);

		if (Chance <= SpawnChance)
		{
			GetWorld()->SpawnActor<AEnemyAI>(Enemies[FMath::RandRange(0, Enemies.Num() - 1)], Cell->Position, FRotator::ZeroRotator);
		}
	}
}