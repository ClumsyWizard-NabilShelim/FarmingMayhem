// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "HouseHealthComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FARMINGMAYHEM_API UHouseHealthComponent : public UHealthComponent
{
	GENERATED_BODY()

protected:
	virtual void Dead() override;
};
