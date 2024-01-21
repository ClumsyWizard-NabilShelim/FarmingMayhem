// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmingPlayerController.h"
#include "DrawDebugHelpers.h"
#include "GridManager.h"
#include "CellObject.h"
#include "InventoryManager.h"
#include "PlayerCharacter.h"
#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUI.h"
#include "Kismet/GameplayStatics.h"
#include "CursorManager.h"
#include "PlayerResourceManager.h"
#include "PlayerResourceManagerUI.h"
#include "ShopManager.h"
#include "ShopManagerUI.h"
#include "FarmingMayhemGameMode.h"

AFarmingPlayerController::AFarmingPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	InventoryManager = CreateDefaultSubobject<UInventoryManager>(TEXT("Inventory Manager"));
	ResourceManager = CreateDefaultSubobject<UPlayerResourceManager>(TEXT("Resource Manager"));
}

void AFarmingPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GridManager = Cast<AFarmingMayhemGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetGridManager();

	InitializeCursorManager();
	InitializePlayerCharacter();
	InitializeHUD();
}

void AFarmingPlayerController::InitializeCursorManager()
{
	Cursor = GetWorld()->SpawnActor(CursorClass);

	if (!Cursor)
		UE_LOG(LogTemp, Error, TEXT("Cursor is null"));

	Cursor->SetOwner(this);


	DefaultCursorSize = Cursor->GetActorScale3D();

	UStaticMeshComponent* Mesh = Cursor->GetComponentByClass<UStaticMeshComponent>();

	if (!Mesh)
		UE_LOG(LogTemp, Error, TEXT("Mesh is null"));

	CursorMaterial = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), Mesh);
	Mesh->SetMaterial(0, CursorMaterial);

	CursorMaterial->SetVectorParameterValue("Tint", FLinearColor::Red);
}

void AFarmingPlayerController::InitializePlayerCharacter()
{
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (!PlayerCharacter)
		UE_LOG(LogTemp, Error, TEXT("PlayerCharacter is null"));

	PlayerCharacter->Initialize(this);
}

void AFarmingPlayerController::InitializeHUD()
{
	HUD = CreateWidget(this, HUDClass);

	if (!HUD)
	{
		UE_LOG(LogTemp, Error, TEXT("HUD is null"));
		return;
	}

	HUD->AddToViewport();

	for (AShopManager* ShopManager : TActorRange<AShopManager>(GetWorld()))
	{
		ShopManager->Initialize(this);
		break;
	}

	UUserWidget* PauseMenu = CreateWidget(this, PauseMenuClass);
	PauseMenu->AddToViewport(10);
}

void AFarmingPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PositionCursor();
}

UCellObject* AFarmingPlayerController::GetCellUnderCursor()
{
	return CellUnderCursor;
}
void AFarmingPlayerController::SetCursorSize(FVector Size)
{
	Cursor->SetActorScale3D(Size);
}
void AFarmingPlayerController::NormalizeCursorSize()
{
	Cursor->SetActorScale3D(DefaultCursorSize);
}
FVector AFarmingPlayerController::GetCursorPosition()
{
	return Cursor->GetActorLocation();
}

bool AFarmingPlayerController::HasCursor()
{
	return IsValid(CellUnderCursor);
}

void AFarmingPlayerController::PositionCursor()
{
	FHitResult HitResult;
	bool bSuccess = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, true, HitResult);

	if (bSuccess)
	{
		UpdateCursor(GridManager->GetCell(HitResult.ImpactPoint), HitResult);
	}
}

void AFarmingPlayerController::UpdateCursor(UCellObject* CellUnder, FHitResult& HitResult)
{
	CellUnderCursor = CellUnder;

	if (!CellUnderCursor)
		return;

	if (!GetPlayerCharacter()->IsInUseRange(CellUnder->Position))
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

	Cursor->SetActorLocation(FVector(CellUnderCursor->Position.X, CellUnderCursor->Position.Y, HitResult.ImpactPoint.Z));
}