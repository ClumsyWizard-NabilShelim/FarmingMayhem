// Fill out your copyright notice in the Description page of Project Settings.


#include "HouseHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FarmingMayhemGameMode.h"

void UHouseHealthComponent::Dead()
{
	Super::Dead();
	Cast<AFarmingMayhemGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GameOver();
}
