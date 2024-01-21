// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingSlot.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGMAYHEM_API UBuildingSlot : public UUserWidget
{
	GENERATED_BODY()
	
private:
	class ABuildManager* BuildManager;
	class UBuildingDataAsset* BuildingData;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateUI(class UBuildingDataAsset* Data);

public:
	UFUNCTION(BlueprintCallable)
	void Initialize(class ABuildManager* SetBuildManager, class UBuildingDataAsset* SetBuildingData);
	UFUNCTION(BlueprintCallable)
	void OnClick();
};
