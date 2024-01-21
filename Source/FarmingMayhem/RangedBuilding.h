// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "RangedBuilding.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGMAYHEM_API ARangedBuilding : public ABuilding
{
	GENERATED_BODY()
	
private:
	//------------Decision Variables------------
	UPROPERTY(EditAnywhere, Category = "Decision") class USphereComponent* DetectionCollider;

	AActor* Target;
	TArray<AActor*> TargetsInRange;
	/************************/

	//------------Combat Variables------------
	UPROPERTY(EditAnywhere, Category = "Combat") float TimeBetweenAttacks;
	UPROPERTY(EditAnywhere, Category = "Combat") TSubclassOf<class AProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Combat") float RotateSpeed;
	UPROPERTY(EditAnywhere, Category = "Combat") class USceneComponent* ShootPoint;
	UPROPERTY(EditAnywhere, Category = "Combat") class UStaticMeshComponent* RotateMesh;
	float CurrentAttackTime;
	/************************/

	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	USoundBase* AttackSound;

public:
	ARangedBuilding();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnTargetEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnTargetExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void GetTargetInRange();
	void AttackTarget();
};