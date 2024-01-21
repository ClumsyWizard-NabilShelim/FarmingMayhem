// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainMenu::AMainMenu()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainMenu::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget(GetWorld(), MenuClass);
	Widget->AddToViewport();

	if (BackgroundMusic != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("BG"));
		UGameplayStatics::PlaySound2D(GetWorld(), BackgroundMusic);
	}
}