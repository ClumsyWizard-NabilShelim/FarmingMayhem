// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FARMINGMAYHEM_API APlayerCharacter : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Locomotion")
	float MoveSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Locomotion")
	float RotateSpeed;
	FVector MoveInput;

	class AFarmingPlayerController* FarmingPlayerController;

	//Holding system
	UPROPERTY(EditDefaultsOnly, Category = "Use Holding")
	float MaxUseRange = 250;
	UPROPERTY(EditDefaultsOnly, Category = "Use Holding")
	float TimeBetweenClick = 0.5f;
	float CurrentClickTime;
	bool bCanUseHolding;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* ItemPivot;
	//Item
	class AItem* CurrentItemActor;
	class UItemDataAsset* CurrentItem;

	//Building
	class UBuildingDataAsset* CurrentBuildingData;
	class ABuilding* CurrentBuilding;



private:
	void Vertical(float Value);
	void Horizontal(float Value);
	void Move(float DeltaTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	APlayerCharacter();
	void Initialize(class AFarmingPlayerController* SetFarmingController);
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool HoldBuilding(UBuildingDataAsset* BuildingData);
	void HoldItem(UItemDataAsset* ItemData);
	void DropItem();
	void UseHolding();
	void Deselect();
	void DeselectHolding(bool bDestroy);
	//Getters
	class UInventoryManager* GetInventoryManager();
	bool IsInUseRange(FVector Position)
	{
		float Distance = (GetActorLocation() - Position).Length();
		return Distance <= MaxUseRange;
	}
};
