// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemFunctionalityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FARMINGMAYHEM_API UItemFunctionalityComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	class UItemDataAsset* DataAsset;

public:	
	// Sets default values for this component's properties
	UItemFunctionalityComponent();
	void Init(UItemDataAsset* SetDataAsset);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	virtual bool OnUseItem(FVector CursorPosition, class UCellObject* UsedOnCell);
};
