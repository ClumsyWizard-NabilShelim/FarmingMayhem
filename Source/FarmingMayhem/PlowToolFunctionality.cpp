// Fill out your copyright notice in the Description page of Project Settings.


#include "PlowToolFunctionality.h"
#include "ItemDataAsset.h"
#include "ToolDataAsset.h"
#include "CellObject.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

UPlowToolFunctionality::UPlowToolFunctionality()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UPlowToolFunctionality::OnUseItem(FVector CursorPosition, UCellObject* UsedOnCell)
{
	if (!UsedOnCell->IsEmpty())
		return false;

	AActor* PlowedGroundEffect = GetWorld()->SpawnActor(PlowedGroundEffectClass);
	PlowedGroundEffect->SetActorLocation(UsedOnCell->Position);
	UsedOnCell->Used(CellHoldingType::PlowedGround, PlowedGroundEffect);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), PlaceEffect, UsedOnCell->Position);

	if (PlaceSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), PlaceSound);
	}

	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CameraShakeClass);

	return true;
}