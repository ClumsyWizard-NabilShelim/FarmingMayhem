// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "House.generated.h"

UCLASS()
class FARMINGMAYHEM_API AHouse : public AActor
{
	GENERATED_BODY()
	
private:
	//------------Components------------

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* Mesh;

	/************************/

public:	
	AHouse();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
