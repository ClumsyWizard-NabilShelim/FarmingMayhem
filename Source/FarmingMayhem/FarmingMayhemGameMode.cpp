// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmingMayhemGameMode.h"
#include "DayNightSystem.h"
#include "Blueprint/UserWidget.h"
#include "RentUI.h"
#include "GameOverUI.h"
#include "Kismet/GameplayStatics.h"
#include "FarmingPlayerController.h"
#include "PlayerResourceManager.h"
#include "EngineUtils.h"
#include "ShopManager.h"

AFarmingMayhemGameMode::AFarmingMayhemGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFarmingMayhemGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayeController = Cast<AFarmingPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!PlayeController)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayeController is null"));
	}

	if (BackgroundMusic != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("BG"));
		UGameplayStatics::PlaySound2D(GetWorld(), BackgroundMusic);
	}
}

void AFarmingMayhemGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	//GridManager
	for (AGridManager* Grid : TActorRange<AGridManager>(GetWorld()))
	{
		GridManager = Grid;
		break;
	}

	//Shop Manager
	for (AShopManager* Shop: TActorRange<AShopManager>(GetWorld()))
	{
		ShopManager = Shop;
		break;
	}

	//DayNightSystem setup
	DayNightSystem = GetComponentByClass<UDayNightSystem>();

	if (!DayNightSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("Day Night System is null"));
	}

	DayNightSystem->StartTime();

	//Rent System UI setup
	RentWidget = Cast<URentUI>(CreateWidget(GetWorld(), RentWidgetClass));

	if (!RentWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("Rent Widget is null"));
	}

	RentWidget->SetVisibility(ESlateVisibility::Hidden);
	RentWidget->AddToViewport(2);
	RentWidget->Initialize(this);

	RentsMissed = 1;

	//GameOver UI setup
	GameOverWidget = Cast<UGameOverUI>(CreateWidget(GetWorld(), GameOverUIClass));

	if (!GameOverWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("GameOver Widget is null"));
	}

	GameOverWidget->SetVisibility(ESlateVisibility::Hidden);
	GameOverWidget->AddToViewport(2);
	GameOverWidget->Initialize(this);

	//GameOver UI setup
	UUserWidget* TutorialWidget = CreateWidget(GetWorld(), TutorialWidgetClass);

	if (!TutorialWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("TutorialWidget Widget is null"));
	}

	TutorialWidget->AddToViewport(5);
}

void AFarmingMayhemGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(RentWidget->GetVisibility() == ESlateVisibility::Hidden)
		UpdateRentTime(DeltaTime);

}

void AFarmingMayhemGameMode::PayRent()
{
	if (PlayeController->GetResourceManager()->GetResource(ResourceType::Coin).StackCount < GetDueRent())
		return;

	PlayeController->GetResourceManager()->RemoveResource(ResourceType::Coin, GetDueRent());
	TotalRentPaid += GetDueRent();
	RentsMissed = 1;
	ToggleRentPayScreen(false);
}

void AFarmingMayhemGameMode::PayLater()
{
	RentsMissed++;
	ToggleRentPayScreen(false);

	if (RentsMissed > MaxAllowedRentMisses)
	{
		GameOver();
	}
}

void AFarmingMayhemGameMode::GameOver()
{
	DayNightSystem->StopTime();
	GameOverWidget->UpdateUI();
	GameOverWidget->SetVisibility(ESlateVisibility::Visible);
}

void AFarmingMayhemGameMode::UpdateRentTime(float DeltaTime)
{
	if (CurrentRentTime > DaysBetweenRent * DayNightSystem->GetSecondsPerDay())
	{
		ToggleRentPayScreen(true);
	}
	else
	{
		CurrentRentTime += DeltaTime * DayNightSystem->GetTimeElapseSpeed();
	}
}

void AFarmingMayhemGameMode::ToggleRentPayScreen(bool bShow)
{
	if (bShow)
	{
		RentWidget->UpdateUI(GetDueRent());
		RentWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		CurrentRentTime = 0.0f;
		RentWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}