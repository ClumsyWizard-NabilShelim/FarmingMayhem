// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class FARMINGMAYHEM_API AProjectile : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Components")
	class USphereComponent* Collider;
	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "Components")
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, Category = "Combat")
	int Damage;

	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	class UNiagaraSystem* HitEffect;
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	FColor HitEffectColor;

public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void Hit(UPrimitiveComponent* ThisOverlappedComponent, AActor* HitActor, UPrimitiveComponent* HitComp, int32 HitBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
