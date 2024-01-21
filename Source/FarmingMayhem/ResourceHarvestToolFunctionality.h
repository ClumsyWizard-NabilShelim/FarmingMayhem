// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemFunctionalityComponent.h"
#include "ResourceHarvestToolFunctionality.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FARMINGMAYHEM_API UResourceHarvestToolFunctionality : public UItemFunctionalityComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ResourceType> HarvestableType;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> CameraShakeClass;

public:
	UResourceHarvestToolFunctionality();
	virtual bool OnUseItem(FVector CursorPosition, class UCellObject* UsedOnCell) override;
};
