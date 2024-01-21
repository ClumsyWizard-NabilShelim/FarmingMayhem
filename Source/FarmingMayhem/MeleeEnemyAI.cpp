// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemyAI.h"
#include "Kismet/GameplayStatics.h"

void AMeleeEnemyAI::Attack(AActor* DamageActor)
{
	Super::Attack(DamageActor);
	UGameplayStatics::ApplyDamage(DamageActor, Damage, GetInstigatorController(), this, UDamageType::StaticClass());
}
