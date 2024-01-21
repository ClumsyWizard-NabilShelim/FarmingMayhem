// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "CellObject.h"
#include "ResourceProductDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "ResourceHealthComponent.h"
#include "FarmingPlayerController.h"
#include "PlayerResourceManager.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AResource::AResource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = SceneComponent;

	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	CapsuleCollider->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

void AResource::Initialize(UCellObject* SetCellUnder)
{
	CellUnder = SetCellUnder;
	CellUnder->Used(CellHoldingType::Resource, this);

	UResourceHealthComponent* HealthComponent = GetComponentByClass< UResourceHealthComponent>();

	if (!HealthComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Resource Health Component"));
		return;
	}

	HealthComponent->Initialize(CellUnder, [this]()
	{
		OnDamage();
	}, 
	[this]()
	{
		AFarmingPlayerController* Controller = Cast<AFarmingPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		Controller->GetResourceManager()->AddResource(Type, DropAmount);
	});
}

// Called when the game starts or when spawned
void AResource::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

