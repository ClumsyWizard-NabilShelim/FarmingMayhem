// Fill out your copyright notice in the Description page of Project Settings.


#include "ShotInventorySlot.h"
#include "ItemDataAsset.h"
#include "ShopManager.h"

void UShotInventorySlot::InitializeSlot(AShopManager* SetShopManager, UItemDataAsset* SetData, int SetStackCount, bool bSetIsShopSlot)
{
	ShopManager = SetShopManager;
	Data = SetData;
	StackCount = SetStackCount;
	bIsShopSlot = bSetIsShopSlot;

	UpdateSlotUI(Data, StackCount);
}

void UShotInventorySlot::ClearSlot()
{
	ShopManager = nullptr;
	Data = nullptr;
	StackCount = 0;
	bIsShopSlot = false;

	OnClearSlot();
}

void UShotInventorySlot::OnPressed()
{
	if (Data == nullptr || ShopManager == nullptr)
		return;

	if(bIsShopSlot)
		ShopManager->Buy(Data);
	else
		ShopManager->Sell(Data);
}
