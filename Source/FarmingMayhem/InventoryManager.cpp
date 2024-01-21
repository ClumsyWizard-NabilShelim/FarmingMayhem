// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManager.h"
#include "ItemDataAsset.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUI.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInventoryManager::UInventoryManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventoryManager::SetInventoryUI(UUserWidget* SetInventoryUI)
{
	InventoryUI = Cast<UInventoryUI>(SetInventoryUI);

	if (!InventoryUI)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryUI is null"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("InventoryUI init"));
	InventoryUI->InitializeUI();

	for (UItemDataAsset* Item : StartingItems)
	{
		AddItem(Item);
	}
}

// Called when the game starts
void UInventoryManager::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < SlotCount; i++)
	{
		InventoryItems.Add(FInventoryData(nullptr, 0));
	}
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void UInventoryManager::AddItem(UItemDataAsset* ItemData)
{
	if (EmptySlotIndex >= SlotCount)
		return;

	for (int i = 0; i < InventoryItems.Num(); i++)
	{
		if (InventoryItems[i].ItemData == ItemData)
		{
			InventoryItems[i].StackCount++;
			InventoryUI->UpdateUI(InventoryItems);
			return;
		}
	}

	InventoryItems[EmptySlotIndex].ItemData = ItemData;
	InventoryItems[EmptySlotIndex].StackCount++;

	InventoryUI->UpdateUI(InventoryItems);

	EmptySlotIndex++;
}

const int UInventoryManager::RemoveItem(UItemDataAsset* ItemData)
{
	int StackCount = 0;
	for (int i = 0; i < InventoryItems.Num(); i++)
	{
		if (InventoryItems[i].ItemData != ItemData)
			continue;

		InventoryItems[i].StackCount--;
		StackCount = InventoryItems[i].StackCount;
		if (InventoryItems[i].StackCount <= 0)
		{
			InventoryItems.RemoveAt(i);
			InventoryItems.Add(FInventoryData(nullptr, 0));
			StackCount = 0;
		}
		EmptySlotIndex = i;
		break;
	}
	for (int i = 0; i < InventoryItems.Num(); i++)
	{
		if (InventoryItems[i].ItemData != nullptr)
			continue;

		EmptySlotIndex = i;
		break;
	}

	InventoryUI->UpdateUI(InventoryItems);
	return StackCount;
}

void UInventoryManager::OnSlotClick(int Index)
{
	if (!InventoryItems[Index].ItemData)
		return;

	PlayerCharacter->HoldItem(InventoryItems[Index].ItemData);
}