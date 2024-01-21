// Fill out your copyright notice in the Description page of Project Settings.


#include "Plant.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "CellObject.h"
#include "PlantProductDataAsset.h"
#include "SeedItemDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "DayNightSystem.h"
#include "FarmingMayhemGameMode.h"
#include "IndicatorUI.h"
#include "Components/WidgetComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

APlant::APlant()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = SceneComponent;

	MeshBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Base"));
	MeshBase->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(MeshBase);
}

void APlant::Initialize(USeedItemDataAsset* SetSeedDataAsset, UCellObject* SetPlantedOnCell)
{
	SeedDataAsset = SetSeedDataAsset;

	UDayNightSystem* DayNightSystem = Cast<AFarmingMayhemGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetDayNightSystem();
	SecondsPerDay = DayNightSystem->GetSecondsPerDay();
	GrowTime = SecondsPerDay * SeedDataAsset->DaysToGrow;
	TimeElapseSpeed = DayNightSystem->GetTimeElapseSpeed();

	CurrentGrowTime = 0.0f;
	PlantedOnCell = SetPlantedOnCell;
	PlowedGroundEffect = PlantedOnCell->GetPlacedActor();

	GrownScale = MeshBase->GetComponentScale();
	StartingScale = MeshBase->GetComponentScale() * 0.1f;
	MeshBase->SetWorldScale3D(StartingScale);

	bIsGrown = false;
	bIsWatered = false;

	Indicator = Cast<UIndicatorUI>(GetComponentByClass<UWidgetComponent>()->GetWidget());
	Indicator->SetIcon(WaterDropletIcon);
	Indicator->Toggle(true);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), PlaceEffect, SetPlantedOnCell->Position);
}

void APlant::BeginPlay()
{
	Super::BeginPlay();
	if (PlaceSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), PlaceSound);
	}
}

// Called every frame
void APlant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsWatered)
		return;

	Grow(DeltaTime);
}

void APlant::Grow(float DeltaTime)
{
	if (CurrentGrowTime > GrowTime)
	{
		ProduceProduct();
		Destroy();
		return;
	}

	if (CurrentDryTime > SecondsPerDay)
	{
		bIsWatered = false;
		CurrentDryTime = 0.0f;
		Indicator->Toggle(true);
		return;
	}

	CurrentGrowTime += DeltaTime * TimeElapseSpeed;
	CurrentDryTime += DeltaTime * TimeElapseSpeed;

	MeshBase->SetWorldScale3D(FMath::Lerp(StartingScale, GrownScale, CurrentGrowTime / GrowTime));
}

void APlant::Water()
{
	CurrentDryTime = 0.0f;
	bIsWatered = true;
	Indicator->Toggle(false);
}

void APlant::ProduceProduct()
{
	AActor* Actor = GetWorld()->SpawnActor(ProductDataAsset->ActorClass);
	Actor->SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, 50.0f));

	PlantedOnCell->Used(CellHoldingType::None, nullptr);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), PlaceEffect, GetActorLocation());
	PlowedGroundEffect->Destroy();
}