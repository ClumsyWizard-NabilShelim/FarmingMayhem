// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAI.h"
#include "MeleeEnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGMAYHEM_API AMeleeEnemyAI : public AEnemyAI
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	int Damage;

protected:
	virtual void Attack(AActor* DamageActor) override;
};
