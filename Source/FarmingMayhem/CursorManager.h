// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CursorManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FARMINGMAYHEM_API UCursorManager : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Cursor", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> CursorClass;
	UPROPERTY()
	AActor* Cursor;
	UMaterialInstanceDynamic* CursorMaterial;
	class UCellObject* CellUnderCursor;

	class AFarmingPlayerController* FarmingPlayerController;

	FVector DefaultCursorSize;

public:	
	// Sets default values for this component's properties
	UCursorManager();
	void Initialize(class AFarmingPlayerController* SetFarmingPlayerController);
	void Update(class UCellObject* CellUnder, FHitResult& HitResult);
	//void ToggleCursor(bool bToggle);
	UCellObject* GetCellUnderCursor() { return CellUnderCursor; }
	FVector GetCursorPosition() { return Cursor->GetActorLocation(); }
	void SetCursorSize(FVector Size);
	void NormalizeCursorSize();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
