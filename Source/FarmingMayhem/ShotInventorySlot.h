// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShotInventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGMAYHEM_API UShotInventorySlot : public UUserWidget
{
	GENERATED_BODY()

private:
	class AShopManager* ShopManager;
	class UItemDataAsset* Data;
	int StackCount;
	bool bIsShopSlot;
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateSlotUI(UItemDataAsset* ItemData, int ItemStackCount);

	UFUNCTION(BlueprintImplementableEvent)
	void OnClearSlot();

	UFUNCTION(BlueprintCallable)
	void OnPressed();

public:
	void InitializeSlot(AShopManager* ShopManager, UItemDataAsset* SetData, int SetStackCount, bool bSetIsShopSlot);
	void ClearSlot();
};
