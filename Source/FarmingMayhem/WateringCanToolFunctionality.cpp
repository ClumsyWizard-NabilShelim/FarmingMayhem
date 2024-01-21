// Fill out your copyright notice in the Description page of Project Settings.


#include "WateringCanToolFunctionality.h"
#include "CellObject.h"
#include "Plant.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

UWateringCanToolFunctionality::UWateringCanToolFunctionality()
{
}

bool UWateringCanToolFunctionality::OnUseItem(FVector CursorPosition, UCellObject* UsedOnCell)
{
	if (!UsedOnCell->HasPlacedActor(CellHoldingType::Plant))
		return false;

	APlant* Plant = UsedOnCell->GetPlacedActor<APlant>(CellHoldingType::Plant);

	if (!Plant)
		return false;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), WaterEffect, UsedOnCell->Position + FVector(0.0f, 0.0f, 700.0f));
	if (WaterSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), WaterSound);
	}

	Plant->Water();

	return true;
}
