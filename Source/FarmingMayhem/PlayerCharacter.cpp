// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "ItemDataAsset.h"
#include "Item.h"
#include "InventoryManager.h"
#include "FarmingPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "BuildingDataAsset.h"
#include "Building.h"
#include "CellObject.h"
#include "PlayerResourceManager.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(CapsuleComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CapsuleComponent);

	ItemPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Item Pivot"));
	ItemPivot->SetupAttachment(Mesh);
}

void APlayerCharacter::Initialize(AFarmingPlayerController* SetFarmingController)
{
	FarmingPlayerController = SetFarmingController;
}


void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);

	if (CurrentBuilding != nullptr && FarmingPlayerController->GetCellUnderCursor() != nullptr)
		CurrentBuilding->SetActorLocation(FarmingPlayerController->GetCellUnderCursor()->Position);

	if (bCanUseHolding)
		return;

	if (CurrentClickTime <= 0)
	{
		bCanUseHolding = true;
		CurrentClickTime = TimeBetweenClick;
	}
	else
	{
		CurrentClickTime -= DeltaTime;
	}
}

void APlayerCharacter::Move(float DeltaTime)
{
	MoveInput.Normalize();
	FVector MoveDirection = MoveInput * MoveSpeed * DeltaTime;

	FRotator Rotator = FRotator(0.0f, 45.0f, 0.0f);
	MoveDirection = Rotator.RotateVector(MoveDirection);
	MoveDirection.Z = 0.0f;
	AddActorLocalOffset(MoveDirection, true);

	if (MoveDirection == FVector::ZeroVector)
		return;

	FRotator LookAtRotation = FRotator(0.0f, MoveDirection.Rotation().Yaw, 0.0f);
	Mesh->SetWorldRotation(FMath::RInterpTo(Mesh->GetComponentRotation(), LookAtRotation, DeltaTime, RotateSpeed));
}

// Input Management
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &APlayerCharacter::Vertical);
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &APlayerCharacter::Horizontal);

	PlayerInputComponent->BindAction(TEXT("DropItem"), EInputEvent::IE_Pressed, this, &APlayerCharacter::DropItem);
	PlayerInputComponent->BindAction(TEXT("UseHolding"), EInputEvent::IE_Pressed, this, &APlayerCharacter::UseHolding);
	PlayerInputComponent->BindAction(TEXT("DeselectHolding"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Deselect);
}

void APlayerCharacter::Vertical(float Value)
{
	MoveInput.X = Value;
}

void APlayerCharacter::Horizontal(float Value)
{
	MoveInput.Y = -Value;
}

bool APlayerCharacter::HoldBuilding(UBuildingDataAsset* BuildingData)
{
	if (FarmingPlayerController->GetResourceManager()->GetResource(ResourceType::Wood).StackCount < BuildingData->WoodCost ||
		FarmingPlayerController->GetResourceManager()->GetResource(ResourceType::Stone).StackCount < BuildingData->StoneCost)
	{
		return false;
	}

	if (CurrentItemActor)
	{
		CurrentItemActor->Destroy();
		CurrentItemActor = nullptr;
		CurrentItem = nullptr;
	}

	CurrentBuildingData = BuildingData;
	CurrentBuilding = Cast<ABuilding>(GetWorld()->SpawnActor(CurrentBuildingData->ActorClass));
	FarmingPlayerController->SetCursorSize(FVector(2.0f, 2.0f, 2.0f));
	return true;
}

//Item and Building
void APlayerCharacter::HoldItem(UItemDataAsset* ItemData)
{
	DeselectHolding(true);

	if (CurrentItem == ItemData)
	{
		UE_LOG(LogTemp, Warning, TEXT("Already holding: %s"), *CurrentItem->Name);
		return;
	}

	if (CurrentItemActor)
		CurrentItemActor->Destroy();

	CurrentItemActor = Cast<AItem>(GetWorld()->SpawnActor(ItemData->ActorClass));

	if (!CurrentItemActor)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn item: %s"), *ItemData->Name);
		return;
	}

	CurrentItem = ItemData;
	CurrentItemActor->SetHolding(true);
	CurrentItemActor->AttachToComponent(ItemPivot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void APlayerCharacter::DropItem()
{
	if (!CurrentItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not holding any item"));
		return;
	}

	int RemainingStackCount = FarmingPlayerController->GetInventoryManager()->RemoveItem(CurrentItem);

	if (RemainingStackCount > 0)
	{
		AActor* SpawnedActor = GetWorld()->SpawnActor(CurrentItem->ActorClass);
		SpawnedActor->SetActorLocation(CurrentItemActor->GetActorLocation());
	}
	else
	{
		CurrentItemActor->DetachAllSceneComponents(ItemPivot, FDetachmentTransformRules::KeepWorldTransform);
		CurrentItemActor->SetHolding(false);
		CurrentItemActor = nullptr;
		CurrentItem = nullptr;
	}
}
void APlayerCharacter::DeselectHolding(bool bDestroy)
{
	CurrentBuildingData = nullptr;
	if (CurrentBuilding != nullptr && bDestroy)
		CurrentBuilding->Destroy();
	CurrentBuilding = nullptr;

	FarmingPlayerController->NormalizeCursorSize();
}

void APlayerCharacter::UseHolding()
{
	if (!bCanUseHolding)
		return;

	if (!IsInUseRange(FarmingPlayerController->GetCellUnderCursor()->Position))
		return;

	if (CurrentBuildingData)
	{
		if (!FarmingPlayerController->GetCellUnderCursor()->IsEmpty())
			return;

		FarmingPlayerController->GetResourceManager()->RemoveResource(ResourceType::Wood, CurrentBuildingData->WoodCost);
		FarmingPlayerController->GetResourceManager()->RemoveResource(ResourceType::Stone, CurrentBuildingData->StoneCost);
		CurrentBuilding->Place(FarmingPlayerController->GetCellUnderCursor());
		DeselectHolding(false);
	}
	else
	{
		if (!CurrentItemActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Nothing to use"));
			return;
		}

		bool bSuccessfulUse = CurrentItemActor->Use(FarmingPlayerController->GetCursorPosition(), FarmingPlayerController->GetCellUnderCursor());

		if (bSuccessfulUse && CurrentItem->bCanDeplete)
		{
			int RemainingStackCount = FarmingPlayerController->GetInventoryManager()->RemoveItem(CurrentItem);
			if (RemainingStackCount <= 0)
			{
				CurrentItemActor->Destroy();
				CurrentItemActor = nullptr;
				CurrentItem = nullptr;
			}
		}
	}

	bCanUseHolding = false;
}
void APlayerCharacter::Deselect()
{
	DeselectHolding(true);
}
//Getters
UInventoryManager* APlayerCharacter::GetInventoryManager()
{
	return FarmingPlayerController->GetInventoryManager();
}