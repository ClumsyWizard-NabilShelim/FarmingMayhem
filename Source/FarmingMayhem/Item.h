// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class FARMINGMAYHEM_API AItem : public AActor
{
	GENERATED_BODY()
	
private:	
	UPROPERTY(EditAnywhere)
	class USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	class UItemDataAsset* Data;
	UItemFunctionalityComponent* Functionality;
	bool bIsHolding;

	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	class UNiagaraSystem* PickUpEffect;
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio") 
	USoundBase* PickUpSound;

private:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	AItem();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* ThisComponent, AActor* HitActor, UPrimitiveComponent* HitComp, int32 HitBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	bool Use(FVector CursorPosition, class UCellObject* UsedOnCell);
	void SetHolding(bool bSetIsHolding) { bIsHolding = bSetIsHolding; }
};
