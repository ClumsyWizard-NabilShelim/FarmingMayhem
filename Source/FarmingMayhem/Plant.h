// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plant.generated.h"

UCLASS()
class FARMINGMAYHEM_API APlant : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Components")
	class USceneComponent* SceneComponent;
	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* MeshBase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	class UPlantProductDataAsset* ProductDataAsset;

	//Visuals and Audio
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	class UNiagaraSystem* PlaceEffect;
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	USoundBase* PlaceSound;

	//Growing
	class USeedItemDataAsset* SeedDataAsset;

	float SecondsPerDay;
	float GrowTime;
	float TimeElapseSpeed;
	float CurrentGrowTime;

	bool bIsGrown;

	FVector StartingScale;
	FVector GrownScale;

	class UCellObject* PlantedOnCell;
	AActor* PlowedGroundEffect;

	//Watering
	bool bIsWatered;
	float CurrentDryTime;
	class UIndicatorUI* Indicator;
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	class UTexture2D* WaterDropletIcon;

public:	
	// Sets default values for this actor's properties
	APlant();
	void Initialize(USeedItemDataAsset* SeedDataAsset, UCellObject* SetPlantedOnCell);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Grow(float DeltaTime);

	void ProduceProduct();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Water();
};
