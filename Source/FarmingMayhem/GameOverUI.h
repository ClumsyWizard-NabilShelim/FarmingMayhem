// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUI.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGMAYHEM_API UGameOverUI : public UUserWidget
{
	GENERATED_BODY()
	
private:
	class AFarmingMayhemGameMode* GameMode;

public:
	void Initialize(class AFarmingMayhemGameMode* SetGameMode);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateUI();
private:
	UFUNCTION(BlueprintCallable)
	int GetDaysSurvived();
	UFUNCTION(BlueprintCallable)
	int GetTotalEarned();
	UFUNCTION(BlueprintCallable)
	int GetTotalSpent();

	UFUNCTION(BlueprintCallable)
	void TryAgain();

	UFUNCTION(BlueprintCallable)
	void Quit();
};
