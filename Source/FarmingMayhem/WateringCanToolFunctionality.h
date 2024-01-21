// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemFunctionalityComponent.h"
#include "WateringCanToolFunctionality.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FARMINGMAYHEM_API UWateringCanToolFunctionality : public UItemFunctionalityComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	class UNiagaraSystem* WaterEffect;
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	USoundBase* WaterSound;

public:
	UWateringCanToolFunctionality();
	virtual bool OnUseItem(FVector CursorPosition, class UCellObject* UsedOnCell) override;
};
