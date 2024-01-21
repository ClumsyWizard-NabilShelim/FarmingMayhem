// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "ResourceHealthComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FARMINGMAYHEM_API UResourceHealthComponent : public UHealthComponent
{
	GENERATED_BODY()

private:
	class UCellObject* CellUnder;
	TFunction<void()> OnDamaged;
	TFunction<void()> OnDead;
	
protected:
	virtual void Dead() override;
	virtual void Damage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) override;
public:
	void Initialize(UCellObject* SetCellUnder, TFunction<void()> SetOnDamaged, TFunction<void()> SetOnDead);
};
