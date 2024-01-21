// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResourceGenerator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FARMINGMAYHEM_API UResourceGenerator : public UActorComponent
{
	GENERATED_BODY()

private:

	class AGridManager* GridManager;

	UPROPERTY(EditAnywhere, Category = "Resource Generation", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AResource>> Resources;

	UPROPERTY(EditAnywhere, Category = "Resource Generation", meta = (AllowPrivateAccess = "true"))
	int ChanceToSpawnPerTile = 100;
	UPROPERTY(EditAnywhere, Category = "Resource Generation", meta = (AllowPrivateAccess = "true"))
	int KeepEmptyCellsRadius;
	UPROPERTY(EditAnywhere, Category = "Resource Generation", meta = (AllowPrivateAccess = "true"))
	float MaxRegenerationDelay;
	UPROPERTY(EditAnywhere, Category = "Resource Generation", meta = (AllowPrivateAccess = "true"))
	float MinRegenerationDelay;
	UPROPERTY(EditAnywhere, Category = "Resource Generation", meta = (AllowPrivateAccess = "true"))
	int ChanceToReSpawnPerTile = 100;
	float CurrentRegenerationTime;

	TArray<class UCellObject*> KeepEmptyCells;

public:	
	// Sets default values for this component's properties
	UResourceGenerator();
	void Initialize(class AGridManager* SetGridManager);
	void GenerateResource(float SpawnChance);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
