// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemDataAsset.h"
#include "PlayerResourceManager.h"
#include "InventoryManager.h"
#include "Resource.h"
#include "ShopManagerUI.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGMAYHEM_API UShopManagerUI : public UUserWidget
{
	GENERATED_BODY()
	
private:
	class AShopManager* ShopManager;
	TArray<class UShotInventorySlot*> ShopSlots;
	TArray<class UShotInventorySlot*> PlayerSlots;

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void CreateSlots(int SlotCount, bool bIsShopSlots);

public:
	void Initialize(AShopManager* SetShopManager);

	UFUNCTION(BlueprintCallable)
	AShopManager* GetShopManager();

	UFUNCTION(BlueprintCallable)
	void SetSlots(TArray<class UShotInventorySlot*> SetSlots, bool bIsShopSlots);

	void UpdateInventoryUI(const TArray<FInventoryData>& Inventory, bool bIsShopSlots);
};
