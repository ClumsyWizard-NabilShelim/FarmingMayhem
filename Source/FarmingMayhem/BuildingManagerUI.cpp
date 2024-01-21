// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingManagerUI.h"
#include "BuildManager.h"
#include "Building.h"

void UBuildingManagerUI::Initialize(ABuildManager* SetBuildManager)
{
	BuildManager = SetBuildManager;
}