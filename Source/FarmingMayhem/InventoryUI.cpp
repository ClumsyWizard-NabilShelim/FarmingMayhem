// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryUI.h"
#include "InventorySlot.h"
#include "ItemDataAsset.h"
#include "InventoryManager.h"

void UInventoryUI::SetSlots(TArray<UInventorySlot*> SetSlots)
{
	Slots = SetSlots;
}

void UInventoryUI::UpdateUI(TArray<FInventoryData> Items)
{
	int CurrentIndex = 0;
	for (int i = 0; i < Slots.Num(); i++)
	{
		Slots[i]->ClearSlot();
	}

	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i].ItemData == nullptr)
			continue;

		Slots[CurrentIndex]->InitializeSlot(Items[i].ItemData, Items[i].StackCount);
		CurrentIndex++;
	}
}