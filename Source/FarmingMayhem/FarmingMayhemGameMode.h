// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FarmingMayhemGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGMAYHEM_API AFarmingMayhemGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	class AGridManager* GridManager;
	class UDayNightSystem* DayNightSystem;
	class AShopManager* ShopManager;
	class AFarmingPlayerController* PlayeController;

	//---------Rent System----------
	UPROPERTY(EditAnywhere, Category = "Rent System")
	int WeeklyRent;
	UPROPERTY(EditAnywhere, Category = "Rent System")
	int MaxAllowedRentMisses;
	int RentsMissed;
	int TotalRentPaid;

	UPROPERTY(EditAnywhere, Category = "Rent System")
	int DaysBetweenRent;
	float CurrentRentTime;
	UPROPERTY(EditAnywhere, Category = "Rent System")
	TSubclassOf<class UUserWidget> RentWidgetClass;
	class URentUI* RentWidget;
	/******************************/

	//---------Game Over----------
	UPROPERTY(EditAnywhere, Category = "Game Over")
	TSubclassOf<class UUserWidget> GameOverUIClass;
	class UGameOverUI* GameOverWidget;
	/******************************/

	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	USoundBase* BackgroundMusic;

	UPROPERTY(EditAnywhere, Category = "Tutorial System")
	TSubclassOf<class UUserWidget> TutorialWidgetClass;

public:
	AFarmingMayhemGameMode();

private:
	void UpdateRentTime(float DeltaTime);
	void ToggleRentPayScreen(bool bShow);

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	AShopManager* GetShopManager() { return ShopManager; }
	UFUNCTION(BlueprintCallable)
	UDayNightSystem* GetDayNightSystem() { return DayNightSystem; }
	AGridManager* GetGridManager() { return GridManager; }

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	int GetDueRent() { return WeeklyRent * RentsMissed; }
	void PayRent();
	void PayLater();
	void GameOver();
};