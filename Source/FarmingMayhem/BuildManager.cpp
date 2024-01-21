// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildManager.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "BuildingManagerUI.h"
#include "BuildingDataAsset.h"

ABuildManager::ABuildManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABuildManager::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (PlayerCharacter == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter is null"));
		return;
	}

	UIManager = Cast<UBuildingManagerUI>(CreateWidget(GetWorld(), UIClass));

	if (UIManager == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UIManager is null"));
		return;
	}

	UIManager->Initialize(this);
	UIManager->AddToViewport(1);
}

void ABuildManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuildManager::BuildingSelected(UBuildingDataAsset* SeletedBuildingData)
{
	bool bSuccess = PlayerCharacter->HoldBuilding(SeletedBuildingData);

	if(bSuccess)
		UIManager->Close();
}
