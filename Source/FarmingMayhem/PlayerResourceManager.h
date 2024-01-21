// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Resource.h"
#include "PlayerResourceManager.generated.h"

struct ResourceData
{
	int StackCount;

	ResourceData(int SetStackCount)
	{
		StackCount = SetStackCount;
	}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FARMINGMAYHEM_API UPlayerResourceManager : public USceneComponent
{
	GENERATED_BODY()

private:
	TMap<ResourceType, ResourceData> Resource;
	class UPlayerResourceManagerUI* ResourceUI;

	//Stats tracking
	int TotalEarned;
	int TotalSpent;

public:	
	// Sets default values for this component's properties
	UPlayerResourceManager();
	UFUNCTION(BlueprintCallable)
	void InitializeUI(UUserWidget* ResourceWidget);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AddResource(ResourceType Type, int Amount);
	void RemoveResource(ResourceType Type, int Amount);
	const TMap<ResourceType, ResourceData>& GetResources() { return Resource; }
	const ResourceData& GetResource(ResourceType Type) { return Resource[Type]; }

	int GetTotalEarned()
	{
		return TotalEarned;
	}
	int GetTotalSpent()
	{
		return TotalSpent;
	}
};
