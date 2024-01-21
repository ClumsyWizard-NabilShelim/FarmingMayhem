// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedEnemyAI.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

ARangedEnemyAI::ARangedEnemyAI()
{
	ShootPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Shoot Point"));
	ShootPoint->SetupAttachment(Mesh);
}

void ARangedEnemyAI::Attack(AActor* DamageActor)
{
	Super::Attack(DamageActor);
	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ShootPoint->GetComponentLocation(), ShootPoint->GetComponentRotation());
}
