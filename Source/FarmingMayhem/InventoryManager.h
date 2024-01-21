// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InventoryManager.generated.h"

USTRUCT(Blueprintable)
struct FInventoryData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UItemDataAsset* ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StackCount;

	FInventoryData() {}

	FInventoryData(UItemDataAsset* ItemData, int StackCount)
	{
		this->ItemData = ItemData;
		this->StackCount = StackCount;
	}
};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FARMINGMAYHEM_API UInventoryManager : public USceneComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int SlotCount;
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<UItemDataAsset*> StartingItems;

	class UInventoryUI* InventoryUI;
	int EmptySlotIndex;
	TArray<FInventoryData> InventoryItems;

	class APlayerCharacter* PlayerCharacter;

public:	
	UInventoryManager();
	UFUNCTION(BlueprintCallable)
	void SetInventoryUI(class UUserWidget* SetInventoryUI);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Getter
	UFUNCTION(BlueprintPure)
	inline int GetSlotCount() { return SlotCount - 1; }

public:
	void AddItem(UItemDataAsset* ItemData);
	const int RemoveItem(UItemDataAsset* ItemData);
	const TArray<FInventoryData>& GetInventoryItem() { return InventoryItems; }
	UFUNCTION(BlueprintCallable)
	void OnSlotClick(int Index);
};