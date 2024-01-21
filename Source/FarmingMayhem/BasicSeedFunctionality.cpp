// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicSeedFunctionality.h"
#include "CellObject.h"
#include "Plant.h"
#include "SeedItemDataAsset.h"

UBasicSeedFunctionality::UBasicSeedFunctionality()
{
}

bool UBasicSeedFunctionality::OnUseItem(FVector CursorPosition, UCellObject* UsedOnCell)
{
	if (!UsedOnCell->HasPlacedActor(CellHoldingType::PlowedGround))
	{
		UE_LOG(LogTemp, Warning, TEXT("Ground is not plowed"));
		return false;
	}
	USeedItemDataAsset* Data = (USeedItemDataAsset*)DataAsset;

	if (!Data)
	{
		UE_LOG(LogTemp, Warning, TEXT("Data is null"));
		return false;
	}

	APlant* Plant = Cast<APlant>(GetWorld()->SpawnActor(Data->PlantClass));
	
	if (!Plant)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn plant"));
		return false;
	}

	Plant->Initialize(Data, UsedOnCell);
	Plant->SetActorLocation(CursorPosition);
	UsedOnCell->Used(CellHoldingType::Plant, Plant);
	return true;
}
