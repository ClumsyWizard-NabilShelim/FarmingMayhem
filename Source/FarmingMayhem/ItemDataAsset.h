// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGMAYHEM_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString Name;
	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;
	UPROPERTY(EditAnywhere)
	FString Description;
	UPROPERTY(EditAnywhere)
	int SellValue;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorClass;
	UPROPERTY(EditAnywhere)
	bool bCanDeplete;

public:
	UFUNCTION(BlueprintPure)
	FString GetName() { return Name; }

	UFUNCTION(BlueprintPure)
	UTexture2D* GetIcon() { return Icon; }
	UFUNCTION(BlueprintPure)
	int GetSellValue() { return SellValue; }
};
