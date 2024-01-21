// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IndicatorUI.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGMAYHEM_API UIndicatorUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetIcon(UTexture2D* Icon);
	UFUNCTION(BlueprintImplementableEvent)
	void SetDisplayText(const FString& Text);

	UFUNCTION(BlueprintImplementableEvent)
	void Toggle(bool toggle);
};
