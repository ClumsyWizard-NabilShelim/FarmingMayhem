// Fill out your copyright notice in the Description page of Project Settings.


#include "RentUI.h"
#include "FarmingMayhemGameMode.h"

void URentUI::Initialize(AFarmingMayhemGameMode* SetGameMode)
{
	GameMode = SetGameMode;
}

int URentUI::GetDueRent()
{
	return GameMode->GetDueRent();
}

void URentUI::PayRent()
{
	UE_LOG(LogTemp, Warning, TEXT("Rent Paid"));
	GameMode->PayRent();
}

void URentUI::PayLater()
{
	UE_LOG(LogTemp, Warning, TEXT("Pay Later"));
	GameMode->PayLater();
}
