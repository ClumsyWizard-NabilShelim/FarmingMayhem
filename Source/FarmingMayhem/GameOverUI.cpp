// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverUI.h"
#include "Kismet/KismetSystemLibrary.h"
#include "FarmingMayhemGameMode.h"
#include "FarmingPlayerController.h"
#include "PlayerResourceManager.h"
#include "DayNightSystem.h"
#include "Kismet/GameplayStatics.h"

void UGameOverUI::Initialize(AFarmingMayhemGameMode* SetGameMode)
{
    GameMode = SetGameMode;
}

int UGameOverUI::GetDaysSurvived()
{
    return GameMode->GetDayNightSystem()->GetDaysPassed();
}

int UGameOverUI::GetTotalEarned()
{
    return Cast<AFarmingPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetResourceManager()->GetTotalEarned();
}

int UGameOverUI::GetTotalSpent()
{
    return Cast<AFarmingPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetResourceManager()->GetTotalSpent();
}

void UGameOverUI::TryAgain()
{
    UGameplayStatics::OpenLevel(GetWorld(), *GetWorld()->GetName(), true);
}

void UGameOverUI::Quit()
{
    TEnumAsByte<EQuitPreference::Type> QuitPreference = EQuitPreference::Quit;
    UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), QuitPreference, false);
}
