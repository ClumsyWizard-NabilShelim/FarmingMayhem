// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyAI.generated.h"

UCLASS()
class FARMINGMAYHEM_API AEnemyAI : public AActor
{
	GENERATED_BODY()
	
protected:

	//------------Components------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USphereComponent* Collider;
	/************************/

	//------------Movement Variables------------
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float LookSpeed;
	/************************/

	//------------Decision Variables------------
	UPROPERTY(EditAnywhere, Category = "Decision")
	float DetectionRange;
	UPROPERTY(EditAnywhere, Category = "Decision")
	float StopDistance;
	UPROPERTY(EditAnywhere, Category = "Decision")
	float AttackRange;
	AActor* Target;
	FHitResult HitResult;
	ECollisionChannel CollisionChanel;
	/************************/

	//------------Combat Variables------------
	UPROPERTY(EditAnywhere, Category = "Combat")
	float TimeBetweenAttacks;
	float CurrentAttackTime;
	/************************/

	//Visuals and Audio
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	FColor SpawnEffectColor;
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	FVector SpawnEffectPlaceOffset;
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	class UNiagaraSystem* SpawnEffect;
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	class UNiagaraSystem* EnemyHitEffect;
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	USoundBase* SpawnSound;
	UPROPERTY(EditAnywhere, Category = "Visuals & Audio")
	USoundBase* AttackSound;

public:	
	// Sets default values for this actor's properties
	AEnemyAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Attack(AActor* DamageActor);
	UFUNCTION(BlueprintImplementableEvent)
	void OnAttack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void GetTargetInRange();
	void GetActorsWithTag(FName Tag, TArray<AActor*>& OutTargetActors);
	void MoveToTarget(FVector DirectionToTarget, float DeltaTime);
	void AttackTarget(FVector DirectionToTarget, FVector HitPoint, float DeltaTime);
};
