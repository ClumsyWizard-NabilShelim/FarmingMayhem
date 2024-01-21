// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShopManager.generated.h"

enum ShopState
{
	Away,
	Available,
	MovingOut
};

UCLASS()
class FARMINGMAYHEM_API AShopManager : public AActor
{
	GENERATED_BODY()

protected:
	class AFarmingPlayerController* PlayerController;
	class UDayNightSystem* DayNightSystem;
	class UIndicatorUI* Indicator;
	bool bIsPlayerInRange;
	float CurrentTimeElapsed;
	ShopState ShopState;

	/*************/
	UPROPERTY(EditAnywhere, Category = "Shopping Window")
	int DaysToVisit;
	UPROPERTY(EditAnywhere, Category = "Shopping Window")
	float ShoppingDuration;
	float CurrentShoppingTime;

	/*************/
	UPROPERTY(EditAnywhere, Category = "Ship Movement")
	int MoveToTargetDuration;

	UPROPERTY(EditAnywhere, Category = "Ship Movement")
	float OriginPosition;

	UPROPERTY(EditAnywhere, Category = "Ship Movement")
	float MoveInPosition;

	UPROPERTY(EditAnywhere, Category = "Ship Movement")
	float MoveOutPosition;

	FVector StartPosition;
	FVector TargetPosition;

	/*************/
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> ShopUIWidgetClass;
	class UShopManagerUI* ShopUI;

	UPROPERTY(EditAnywhere, Category = "UI")
	TArray<struct FInventoryData> ShopInventory;
	TArray<struct FInventoryData> CurrentShopInventory;


	/*************/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class UStaticMeshComponent* BoatMesh;
	UPROPERTY(EditAnywhere, Category = "Component")
	class USphereComponent* Collider;

	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	USoundBase* ShopAvailableSound;
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	USoundBase* BuySellSound;
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	USoundBase* DeniedSound;
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	USoundBase* OpenCloseSound;

private:
	void OpenShop();
	UFUNCTION(BlueprintCallable)
	void CloseShop(bool clearCurrentShopInventory);

	void SetupIndicator();
	void UpdateShopUI();

	void ShoppingWindow(float DeltaSeconds);
	void ShipMovement(float DeltaSeconds);

public:	
	AShopManager();
	void Initialize(class AFarmingPlayerController* SetPlayerController);
	void Buy(class UItemDataAsset* Data);
	void Sell(class UItemDataAsset* Data);

	UFUNCTION(BlueprintCallable)
	FString GetDaysToShip()
	{
		float Days = DaysToVisit - CurrentTimeElapsed / 60.0f / 60.0f / 24.0f;
		
		if (Days < 1.0f)
			Days = 1.0f;

		if (ShopState == ShopState::Available)
			return "Shop!";

		return FString::FromInt((int)Days);
	}

public:	
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void SetPlayerInRange(bool bIsInRange);
};
