// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class FARMINGMAYHEM_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

private:
	class UDayNightSystem* DayNightSystem;
	UPROPERTY(EditAnywhere, Category = "Spawn Decision") TArray<TSubclassOf<class AEnemyAI>> Enemies;

	UPROPERTY(EditAnywhere, Category = "Spawn Decision") int MaxDaysBetweenSpawn;
	UPROPERTY(EditAnywhere, Category = "Spawn Decision") int MinDaysBetweenSpawn;
	UPROPERTY(EditAnywhere, Category = "Spawn Decision") int SpawnChance;

	int CurrentDaysBetweenSpawn;
	float CurrentSpawnTime;

	class AGridManager* GridManager;
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SpawnEnemies();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
