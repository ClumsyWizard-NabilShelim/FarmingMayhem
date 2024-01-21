// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "CellObject.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);
}

void ABuilding::Place(UCellObject* CellObject)
{
	bIsActive = true;
	CellObject->Used(CellHoldingType::Occupied, this);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SpawnEffect, CellObject->Position);
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CameraShakeClass);
	if (SpawnSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), SpawnSound);
	}
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();
}
