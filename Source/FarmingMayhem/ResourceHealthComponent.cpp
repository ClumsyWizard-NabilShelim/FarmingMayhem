// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceHealthComponent.h"
#include "CellObject.h"

void UResourceHealthComponent::Dead()
{
	CellUnder->Used(CellHoldingType::None, nullptr);
	OnDead();
	Super::Dead();
}

void UResourceHealthComponent::Damage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::Damage(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
	OnDamaged();
}

void UResourceHealthComponent::Initialize(UCellObject* SetCellUnder, TFunction<void()> SetOnDamaged, TFunction<void()> SetOnDead)
{
	CellUnder = SetCellUnder;
	OnDamaged = SetOnDamaged;
	OnDead = SetOnDead;
}
