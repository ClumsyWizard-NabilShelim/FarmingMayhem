// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerResourceManager.h"
#include "PlayerResourceManagerUI.h"

// Sets default values for this component's properties
UPlayerResourceManager::UPlayerResourceManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UPlayerResourceManager::BeginPlay()
{
	Super::BeginPlay();

	Resource.Add(ResourceType::Coin, ResourceData(200));
	Resource.Add(ResourceType::Wood, ResourceData(0));
	Resource.Add(ResourceType::Stone, ResourceData(0));
}

void UPlayerResourceManager::InitializeUI(UUserWidget* ResourceWidget)
{
	ResourceUI = Cast<UPlayerResourceManagerUI>(ResourceWidget);

	if (!ResourceUI)
		UE_LOG(LogTemp, Error, TEXT("Failed to cast ResourceWidget"));

	
	ResourceUI->UpdateUI(ResourceType::Coin, Resource[ResourceType::Coin].StackCount);
	
	ResourceUI->UpdateUI(ResourceType::Wood, Resource[ResourceType::Wood].StackCount);
	
	ResourceUI->UpdateUI(ResourceType::Stone, Resource[ResourceType::Stone].StackCount);
}


// Called every frame
void UPlayerResourceManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerResourceManager::AddResource(ResourceType Type, int Amount)
{
	Resource[Type].StackCount += Amount;

	if (Type == ResourceType::Coin)
		TotalEarned += Amount;

	ResourceUI->UpdateUI(Type, Resource[Type].StackCount);
}

void UPlayerResourceManager::RemoveResource(ResourceType Type, int Amount)
{
	Resource[Type].StackCount -= Amount;

	if (Type == ResourceType::Coin)
		TotalSpent += Amount;

	ResourceUI->UpdateUI(Type, Resource[Type].StackCount);
}
