// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceHarvestToolFunctionality.h"
#include "CellObject.h"
#include "Kismet/GameplayStatics.h"
#include "Resource.h"
#include "ToolDataAsset.h"

UResourceHarvestToolFunctionality::UResourceHarvestToolFunctionality()
{
}

bool UResourceHarvestToolFunctionality::OnUseItem(FVector CursorPosition, UCellObject* UsedOnCell)
{
	if (!UsedOnCell->HasPlacedActor(CellHoldingType::Resource))
		return false;

	AResource* Resource = UsedOnCell->GetPlacedActor<AResource>(CellHoldingType::Resource);

	if (!Resource || HarvestableType != Resource->Type)
		return false;

	UGameplayStatics::ApplyDamage(Resource, ((UToolDataAsset*)DataAsset)->Damage, GetOwner()->GetInstigatorController(), GetOwner(), UDamageType::StaticClass());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CameraShakeClass);

	return true;
}