// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RentUI.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGMAYHEM_API URentUI : public UUserWidget
{
	GENERATED_BODY()
	
	class AFarmingMayhemGameMode* GameMode;

public:
	void Initialize(class AFarmingMayhemGameMode* SetGameMode);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateUI(int DueRent);

protected:
	UFUNCTION(BlueprintCallable)
	int GetDueRent();
	UFUNCTION(BlueprintCallable)
	void PayRent();
	UFUNCTION(BlueprintCallable)
	void PayLater();

};
