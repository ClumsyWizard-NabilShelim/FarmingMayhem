// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

UCLASS()
class FARMINGMAYHEM_API ABuilding : public AActor
{
	GENERATED_BODY()
	
protected:
	//------------Components------------

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UCapsuleComponent* Collider;
	/************************/

	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	class UNiagaraSystem* SpawnEffect;

	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	USoundBase* SpawnSound;
	bool bIsActive;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> CameraShakeClass;

public:	
	ABuilding();
	void Place(class UCellObject* CellObject);
protected:
	virtual void BeginPlay() override;
};
