// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BuildingDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGMAYHEM_API UBuildingDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere) FString Name;
	UPROPERTY(EditAnywhere) UTexture2D* Icon;
	UPROPERTY(EditAnywhere) FString Description;
	UPROPERTY(EditAnywhere) int WoodCost;
	UPROPERTY(EditAnywhere) int StoneCost;
	UPROPERTY(EditAnywhere) TSubclassOf<class ABuilding> ActorClass;

public:
	UFUNCTION(BlueprintPure)
	FString GetName() { return Name; }

	UFUNCTION(BlueprintPure)
	UTexture2D* GetIcon() { return Icon; }
	UFUNCTION(BlueprintPure)
	int GetWoodCost() { return WoodCost; }
	UFUNCTION(BlueprintPure)
	int GetStoneCost() { return StoneCost; }
};
