// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemFunctionalityComponent.h"
#include "PlowToolFunctionality.generated.h"

/**
 * 
 */

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FARMINGMAYHEM_API UPlowToolFunctionality : public UItemFunctionalityComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	class UNiagaraSystem* PlaceEffect;
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio") 
	USoundBase* PlaceSound;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> PlowedGroundEffectClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> CameraShakeClass;

public:
	UPlowToolFunctionality();
	virtual bool OnUseItem(FVector CursorPosition, class UCellObject* UsedOnCell) override;
};
