// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FarmingPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGMAYHEM_API AFarmingPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	class AGridManager* GridManager;

	UPROPERTY(EditAnywhere, Category = "Pause Menu")
	TSubclassOf<class UUserWidget> PauseMenuClass;

	//Cursor Variables
	UPROPERTY(EditAnywhere, Category = "Cursor", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> CursorClass;
	UPROPERTY()
	AActor* Cursor;
	UMaterialInstanceDynamic* CursorMaterial;
	class UCellObject* CellUnderCursor;

	FVector DefaultCursorSize;
	//*****************

	UPROPERTY(EditAnywhere, Category = "Inventory")
	class UInventoryManager* InventoryManager;
	UPROPERTY(EditAnywhere, Category = "Resource")
	class UPlayerResourceManager* ResourceManager;
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<class UUserWidget> HUDClass;
	class UUserWidget* HUD;

	class APlayerCharacter* PlayerCharacter;

private:
	void InitializeCursorManager();
	void InitializePlayerCharacter();
	void InitializeHUD();
	void UpdateCursor(class UCellObject* CellUnder, FHitResult& HitResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void PositionCursor();
	
public:
	AFarmingPlayerController();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	UInventoryManager* GetInventoryManager() { return InventoryManager; }
	UFUNCTION(BlueprintCallable)
	UPlayerResourceManager* GetResourceManager() { return ResourceManager; }

	class UCellObject* GetCellUnderCursor();
	void SetCursorSize(FVector Size);
	void NormalizeCursorSize();
	UFUNCTION(BlueprintCallable)
	FVector GetCursorPosition();

	UFUNCTION(BlueprintCallable)
	bool HasCursor();
	APlayerCharacter* GetPlayerCharacter() { return PlayerCharacter; }
};
