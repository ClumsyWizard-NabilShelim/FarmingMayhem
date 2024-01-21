// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataAsset.h"
#include "SeedItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGMAYHEM_API USeedItemDataAsset : public UItemDataAsset
{
	GENERATED_BODY()
	
private:
public:
	UPROPERTY(EditAnywhere)
	int DaysToGrow;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class APlant> PlantClass;
};