// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildManager.generated.h"

UCLASS()
class FARMINGMAYHEM_API ABuildManager : public AActor
{
	GENERATED_BODY()
	
private:
	class APlayerCharacter* PlayerCharacter;
	UPROPERTY(EditAnywhere, Category = "Building")
	TArray<class UBuildingDataAsset*> BuildingDatas;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UBuildingManagerUI> UIClass;
	class UBuildingManagerUI* UIManager;
public:	
	ABuildManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	TArray<class UBuildingDataAsset*> GetBuildingDatas() { return BuildingDatas; }
	void BuildingSelected(UBuildingDataAsset* SeletedBuildingData);
};
