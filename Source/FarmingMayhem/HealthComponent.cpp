// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = Health;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::Damage);
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::Damage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	CurrentHealth -= Damage;
	
	if (HitEffect != nullptr)
	{
		UNiagaraComponent* HitEffectComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitEffect, GetOwner()->GetActorLocation() + HitEffectSpawnPointOffset);
		HitEffectComp->SetVariableVec4(TEXT("Color"), FVector4(HitEffectColor));
	}

	if (HitSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), HitSound);
	}

	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CameraShakeHitClass);

	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0;
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CameraShakeDeathClass);
		Dead();
	}
}

void UHealthComponent::Dead()
{
	if (DeathEffect != nullptr)
	{
		UNiagaraComponent* HitEffectComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DeathEffect, GetOwner()->GetActorLocation() + DeathEffectSpawnPointOffset);
		HitEffectComp->SetVariableVec4(TEXT("Color"), FVector4(DeathEffectColor));
	}
	if (DestroySound != nullptr)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), DestroySound);
	}

	GetOwner()->Destroy();
}