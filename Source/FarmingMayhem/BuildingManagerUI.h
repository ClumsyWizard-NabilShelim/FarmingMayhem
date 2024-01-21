// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingManagerUI.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGMAYHEM_API UBuildingManagerUI : public UUserWidget
{
	GENERATED_BODY()
	
private:
	class ABuildManager* BuildManager;

public:
	void Initialize(class ABuildManager* SetBuildManager);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Close();

	UFUNCTION(BlueprintCallable)
	ABuildManager* GetBuildManager() { return BuildManager; }
};
