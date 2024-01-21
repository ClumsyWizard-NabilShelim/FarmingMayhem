// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopManagerUI.h"
#include "ShopManager.h"
#include "ShotInventorySlot.h"

void UShopManagerUI::Initialize(AShopManager* SetShopManager)
{
	ShopManager = SetShopManager;

	CreateSlots(10, true);
	CreateSlots(10, false);
}

AShopManager* UShopManagerUI::GetShopManager()
{
	return ShopManager;
}

void UShopManagerUI::SetSlots(TArray<class UShotInventorySlot*> SetSlots, bool bIsShopSlots)
{
	if(bIsShopSlots)
		ShopSlots = SetSlots;
	else
		PlayerSlots = SetSlots;
}

void UShopManagerUI::UpdateInventoryUI(const TArray<FInventoryData>& Inventory, bool bIsShopSlots)
{
	if (bIsShopSlots)
	{
		for (int i = 0; i < ShopSlots.Num(); i++)
		{
			ShopSlots[i]->ClearSlot();
			if (i < Inventory.Num())
				ShopSlots[i]->InitializeSlot(ShopManager, Inventory[i].ItemData, Inventory[i].StackCount, true);
		}
	}
	else
	{
		int LastAddedIndex = 0;
		for (int i = 0; i < PlayerSlots.Num(); i++)
		{
			PlayerSlots[i]->ClearSlot();
			if (i < Inventory.Num() && Inventory[i].ItemData != nullptr && Inventory[i].ItemData->bCanDeplete)
			{
				PlayerSlots[LastAddedIndex]->InitializeSlot(ShopManager, Inventory[i].ItemData, Inventory[i].StackCount, false);
				LastAddedIndex++;
			}
		}
	}
}
