// Fill out your copyright notice in the Description page of Project Settings.


#include "CursorManager.h"
#include "CellObject.h"
#include "Components/StaticMeshComponent.h"
#include "FarmingPlayerController.h"
#include "PlayerCharacter.h"
#include "DrawDebugHelpers.h"

UCursorManager::UCursorManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCursorManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UCursorManager::Initialize(AFarmingPlayerController* SetFarmingPlayerController)
{
	FarmingPlayerController = SetFarmingPlayerController;

	Cursor = GetWorld()->SpawnActor(CursorClass);

	if (!Cursor)
		UE_LOG(LogTemp, Error, TEXT("Cursor is null"));

	Cursor->SetOwner(FarmingPlayerController);


	DefaultCursorSize = Cursor->GetActorScale3D();

	UStaticMeshComponent* Mesh = Cursor->GetComponentByClass<UStaticMeshComponent>();

	if (!Mesh)
		UE_LOG(LogTemp, Error, TEXT("Mesh is null"));

	CursorMaterial = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), Mesh);
	Mesh->SetMaterial(0, CursorMaterial);

	CursorMaterial->SetVectorParameterValue("Tint", FLinearColor::Red);
}

void UCursorManager::Update(UCellObject* CellUnder, FHitResult& HitResult)
{
	CellUnderCursor = CellUnder;

	if (!CellUnderCursor)
		return;

	if (!FarmingPlayerController->GetPlayerCharacter()->IsInUseRange(CellUnder->Position))
	{
		CursorMaterial->SetVectorParameterValue("Tint", FLinearColor::Red);
	}
	else
	{
		if (CellUnderCursor->IsEmpty())
			CursorMaterial->SetVectorParameterValue("Tint", FLinearColor::White);
		else if (CellUnderCursor->HasPlacedActor(CellHoldingType::PlowedGround) || CellUnderCursor->HasPlacedActor(CellHoldingType::Resource) || CellUnderCursor->HasPlacedActor(CellHoldingType::Plant))
			CursorMaterial->SetVectorParameterValue("Tint", FLinearColor::Green);
		else
			CursorMaterial->SetVectorParameterValue("Tint", FLinearColor::Red);
	}

	//ToggleCursor(true);
	Cursor->SetActorLocation(FVector(CellUnderCursor->Position.X, CellUnderCursor->Position.Y, CellUnderCursor->Position.Z));
	DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 20.0f, 20, FColor::Red, false);
}
//
//void UCursorManager::ToggleCursor(bool bToggle)
//{
//	Cursor->SetActorHiddenInGame(!bToggle);
//}

void UCursorManager::SetCursorSize(FVector Size)
{
	Cursor->SetActorScale3D(Size);
}

void UCursorManager::NormalizeCursorSize()
{
	Cursor->SetActorScale3D(DefaultCursorSize);
}

void UCursorManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}