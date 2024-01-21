// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUI.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGMAYHEM_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()

private:
	TArray<class UInventorySlot*> Slots;
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void InitializeUI();

	void UpdateUI(TArray<struct FInventoryData> Items);
	UFUNCTION(BlueprintCallable)
	void SetSlots(TArray<UInventorySlot*> SetSlots);
};
