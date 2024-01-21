// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "DayNightSystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FARMINGMAYHEM_API UDayNightSystem : public USceneComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Day/Night Cycle")
	float HoursPerDay;
	UPROPERTY(EditAnywhere, Category = "Day/Night Cycle")
	float HoursPerMinute;
	float CurrentTime;
	int DaysPassed;

	bool bPassTime;

public:	
	UDayNightSystem();

protected:
	virtual void BeginPlay() override;

private:
	void PassTime(float DeltaTime);

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void StopTime();
	void StartTime();

	//Getters
	UFUNCTION(BlueprintCallable)
	FString GetCurrentTime()
	{
		int Hour = CurrentTime / 60.0f /60.0f;
		int Seconds = CurrentTime / 60.0f;
		Seconds = Seconds % 60;
		bool bIsLowerThanTen = Seconds < 10;
		return FString::FromInt(Hour) + " :" + (bIsLowerThanTen ? " 0" : "") + FString::FromInt(Seconds);
	}
	float GetTimeElapseSpeed()
	{
		return HoursPerMinute * 60.0f;
	}
	float GetSecondsPerDay()
	{
		return HoursPerDay * 60.0f * 60.0f;
	}
	UFUNCTION(BlueprintCallable)
	int GetDaysPassed()
	{
		return DaysPassed;
	}
};