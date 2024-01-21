// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HealthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FARMINGMAYHEM_API UHealthComponent : public USceneComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	float Health;
	float CurrentHealth;

	//Visuals and Audio
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio") class UNiagaraSystem* HitEffect;
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio") FColor HitEffectColor;
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio") FVector HitEffectSpawnPointOffset;

	UPROPERTY(EditAnywhere, Category = "Visuals & Audio") class UNiagaraSystem* DeathEffect;
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio") FColor DeathEffectColor;
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio") FVector DeathEffectSpawnPointOffset;

	UPROPERTY(EditAnywhere, Category = "Visuals & Audio") USoundBase* HitSound;
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio") USoundBase* DestroySound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> CameraShakeHitClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> CameraShakeDeathClass;

public:	
	UHealthComponent();

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void Damage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	virtual void Dead();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
