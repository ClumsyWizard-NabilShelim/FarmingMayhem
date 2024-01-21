// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerCharacter.h"
#include "InventoryManager.h"
#include "ItemDataAsset.h"
#include "ItemFunctionalityComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();	
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnHit);

	//Functionality = Cast<UItemFunctionalityComponent>(AddComponentByClass(FunctionalityClass, false, GetActorTransform(), false));
	Functionality = Cast<UItemFunctionalityComponent>(GetComponentByClass<UItemFunctionalityComponent>());

	if (!Functionality)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create Functionality Component"));
		return;
	}

	Functionality->Init(Data);
}

void AItem::OnHit(UPrimitiveComponent* ThisOverlappedComponent, AActor* HitActor, UPrimitiveComponent* HitComp, int32 HitBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsHolding)
		return;

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(HitActor);

	if (!PlayerCharacter)
		return;

	PlayerCharacter->GetInventoryManager()->AddItem(Data);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), PickUpEffect, GetActorLocation());


	if (PickUpSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), PickUpSound);
	}

	Destroy();
}

bool AItem::Use(FVector CursorPosition, UCellObject* UsedOnCell)
{
	if (!Functionality)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Functionality Added"));
		return false;
	}
	return Functionality->OnUseItem(CursorPosition, UsedOnCell);
}
