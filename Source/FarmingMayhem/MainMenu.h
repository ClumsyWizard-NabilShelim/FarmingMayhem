// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainMenu.generated.h"

UCLASS()
class FARMINGMAYHEM_API AMainMenu : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> MenuClass;
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	USoundBase* BackgroundMusic;
public:	
	// Sets default values for this actor's properties
	AMainMenu();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
