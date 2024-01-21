// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAI.h"
#include "RangedEnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGMAYHEM_API ARangedEnemyAI : public AEnemyAI
{
	GENERATED_BODY()
	
private:
	//------------Components------------
	UPROPERTY(EditAnywhere, Category = "Components")
	class USceneComponent* ShootPoint;
	/************************/

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProjectileClass;

public:
	// Sets default values for this actor's properties
	ARangedEnemyAI();
protected:
	virtual void Attack(AActor* DamageActor) override;
};
