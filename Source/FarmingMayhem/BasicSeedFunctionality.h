// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemFunctionalityComponent.h"
#include "BasicSeedFunctionality.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FARMINGMAYHEM_API UBasicSeedFunctionality : public UItemFunctionalityComponent
{
	GENERATED_BODY()

public:
	UBasicSeedFunctionality();
	virtual bool OnUseItem(FVector CursorPosition, class UCellObject* UsedOnCell) override;
};
