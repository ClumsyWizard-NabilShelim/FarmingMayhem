// Fill out your copyright notice in the Description page of Project Settings.


#include "DayNightSystem.h"

UDayNightSystem::UDayNightSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDayNightSystem::BeginPlay()
{
	Super::BeginPlay();
}

void UDayNightSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	PassTime(DeltaTime);
}

void UDayNightSystem::PassTime(float DeltaTime)
{
	if (!bPassTime)
		return;

	if (CurrentTime > GetSecondsPerDay())
	{
		CurrentTime = 0.0f;
		DaysPassed++;
		UE_LOG(LogTemp, Warning, TEXT("Days Passes: %d"), DaysPassed);
	}
	else
	{
		CurrentTime += DeltaTime * GetTimeElapseSpeed();
	}
}

void UDayNightSystem::StopTime()
{
	UE_LOG(LogTemp, Warning, TEXT("Time Paused"));
	bPassTime = false;
}
void UDayNightSystem::StartTime()
{
	UE_LOG(LogTemp, Warning, TEXT("Time Started"));
	bPassTime = true;
}