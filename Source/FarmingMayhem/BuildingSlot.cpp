// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSlot.h"
#include "BuildingDataAsset.h"
#include "BuildManager.h"

void UBuildingSlot::Initialize(ABuildManager* SetBuildManager, UBuildingDataAsset* SetData)
{
	BuildManager = SetBuildManager;
	BuildingData = SetData;
	UpdateUI(BuildingData);
}

void UBuildingSlot::OnClick()
{
	BuildManager->BuildingSelected(BuildingData);
}