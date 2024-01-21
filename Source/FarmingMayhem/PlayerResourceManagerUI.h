// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerResourceManagerUI.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGMAYHEM_API UPlayerResourceManagerUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateUI(ResourceType ResourceType, int CurrentAmount);
};
