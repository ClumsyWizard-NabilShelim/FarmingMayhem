// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopManager.h"
#include "ShopManagerUI.h"
#include "IndicatorUI.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FarmingPlayerController.h"
#include "InventoryManager.h"
#include "ShotInventorySlot.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FarmingMayhemGameMode.h"
#include "DayNightSystem.h"
#include <stdlib.h>

// Setup
AShopManager::AShopManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Player In Range Check"));
	RootComponent = Collider;

	BoatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Boat Mesh"));
	BoatMesh->SetupAttachment(Collider);
}

void AShopManager::Initialize(AFarmingPlayerController* SetPlayerController)
{
	PlayerController = SetPlayerController;
	PlayerController->InputComponent->BindAction(TEXT("OpenShop"), EInputEvent::IE_Pressed, this, &AShopManager::OpenShop);

	SetupIndicator();

	ShopUI = Cast<UShopManagerUI>(CreateWidget(PlayerController, ShopUIWidgetClass));
	if (!ShopUI)
	{
		UE_LOG(LogTemp, Error, TEXT("ShopUI is null"));
		return;
	}

	ShopUI->Initialize(this);
	ShopUI->AddToViewport(1);
	ShopUI->SetVisibility(ESlateVisibility::Hidden);

	DayNightSystem = Cast<AFarmingMayhemGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetDayNightSystem();
}

//Update
void AShopManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(ShopState == ShopState::Away)
		ShoppingWindow(DeltaSeconds);
	else
		ShipMovement(DeltaSeconds);
}

//Shop Interaction
void AShopManager::OpenShop()
{
	if (!bIsPlayerInRange || ShopState != ShopState::Available)
		return;

	if (CurrentShopInventory.Num() == 0)
	{
		for (int i = 0; i < ShopInventory.Num(); i++)
		{
			CurrentShopInventory.Add(ShopInventory[i]);
		}
	}

	if (OpenCloseSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), OpenCloseSound);
	}

	ShopUI->SetVisibility(ESlateVisibility::Visible);
	UpdateShopUI();
}
void AShopManager::CloseShop(bool clearCurrentShopInventory)
{
	if (clearCurrentShopInventory)
		CurrentShopInventory.Empty();

	if (OpenCloseSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), OpenCloseSound);
	}

	ShopUI->SetVisibility(ESlateVisibility::Hidden);
}

void AShopManager::Buy(UItemDataAsset* Data)
{
	if (PlayerController->GetResourceManager()->GetResource(ResourceType::Coin).StackCount < Data->SellValue)
	{
		if (DeniedSound != nullptr)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), DeniedSound);
		}
		return;
	}

	PlayerController->GetResourceManager()->RemoveResource(ResourceType::Coin, Data->SellValue);
	PlayerController->GetInventoryManager()->AddItem(Data);

	for (int i = 0; i < CurrentShopInventory.Num(); i++)
	{
		if (CurrentShopInventory[i].ItemData == Data)
		{
			CurrentShopInventory[i].StackCount--;

			if (CurrentShopInventory[i].StackCount <= 0)
			{
				CurrentShopInventory.RemoveAt(i);
			}

			break;
		}
	}

	if (BuySellSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), BuySellSound);
	}

	UpdateShopUI();
}
void AShopManager::Sell(UItemDataAsset* Data)
{
	PlayerController->GetResourceManager()->AddResource(ResourceType::Coin, Data->SellValue);
	PlayerController->GetInventoryManager()->RemoveItem(Data);

	bool bFoundItemInInventory = false;
	for (int i = 0; i < CurrentShopInventory.Num(); i++)
	{
		if (CurrentShopInventory[i].ItemData == Data)
		{
			CurrentShopInventory[i].StackCount++;
			bFoundItemInInventory = true;
			break;
		}
	}

	if (!bFoundItemInInventory)
		CurrentShopInventory.Add(FInventoryData(Data, 1));

	if (BuySellSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), BuySellSound);
	}

	UpdateShopUI();
}

//Helper Functions
void AShopManager::SetupIndicator()
{
	Indicator = Cast<UIndicatorUI>(GetComponentByClass<UWidgetComponent>()->GetWidget());
	const FString Key = "E";
	Indicator->SetDisplayText(Key);
	Indicator->Toggle(false);
}

void AShopManager::UpdateShopUI()
{
	ShopUI->UpdateInventoryUI(CurrentShopInventory, true);
	ShopUI->UpdateInventoryUI(PlayerController->GetInventoryManager()->GetInventoryItem(), false);
}

void AShopManager::ShoppingWindow(float DeltaSeconds)
{
	if (CurrentTimeElapsed > DaysToVisit * DayNightSystem->GetSecondsPerDay())
	{
		if (ShopAvailableSound != nullptr)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), ShopAvailableSound);
		}

		StartPosition = FVector(GetActorLocation().X, OriginPosition, GetActorLocation().Z);
		TargetPosition = FVector(GetActorLocation().X, MoveInPosition, GetActorLocation().Z);
		ShopState = ShopState::Available;
		CurrentTimeElapsed = 0.0f;
		return;
	}

	CurrentTimeElapsed += DeltaSeconds * DayNightSystem->GetTimeElapseSpeed();
}

void AShopManager::ShipMovement(float DeltaSeconds)
{
	if (CurrentTimeElapsed >= MoveToTargetDuration)
	{
		if (ShopState == ShopState::Available)
		{
			if (CurrentShoppingTime < ShoppingDuration)
			{
				CurrentShoppingTime += DeltaSeconds;
				return;
			}

			ShopState = ShopState::MovingOut;
			TargetPosition = FVector(GetActorLocation().X, MoveOutPosition, GetActorLocation().Z);
			StartPosition = FVector(GetActorLocation().X, MoveInPosition, GetActorLocation().Z);
			CurrentTimeElapsed = 0.0f;
			CurrentShoppingTime = 0.0f;

			//Just to make sure that shop closes when moving out
			CloseShop(true);
		}
		else
		{
			ShopState = ShopState::Away;
			SetActorLocation(FVector(GetActorLocation().X, OriginPosition, GetActorLocation().Z));
			CurrentTimeElapsed = 0.0f;
		}

		return;
	}

	CurrentTimeElapsed += DeltaSeconds;

	FVector MoveTo = FMath::Lerp(StartPosition, TargetPosition, CurrentTimeElapsed / MoveToTargetDuration);
	SetActorLocation(MoveTo);
}

void AShopManager::SetPlayerInRange(bool bIsInRange)
{
	bIsPlayerInRange = bIsInRange;
	Indicator->Toggle(bIsPlayerInRange);
}
