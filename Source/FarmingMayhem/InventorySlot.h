// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemDataAsset.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGMAYHEM_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void InitializeSlot(UItemDataAsset* Data, int StackCount);

	UFUNCTION(BlueprintImplementableEvent)
	void ClearSlot();
};
