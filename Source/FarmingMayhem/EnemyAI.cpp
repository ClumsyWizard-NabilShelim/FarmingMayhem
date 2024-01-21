// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAI.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AEnemyAI::AEnemyAI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);
}

// Called when the game starts or when spawned
void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();	
	UNiagaraComponent* SpawnDeadEffectComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SpawnEffect, GetActorLocation() + SpawnEffectPlaceOffset);
	SpawnDeadEffectComp->SetVariableVec4(TEXT("Color"), FVector4(SpawnEffectColor));

	if (SpawnSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), SpawnSound);
	}
}

void AEnemyAI::Attack(AActor* DamageActor)
{
	OnAttack();

	if (AttackSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), AttackSound);
	}
}

// Called every frame
void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*DrawDebugSphere(GetWorld(), GetActorLocation(), DetectionRange, 15, FColor::Green, false);
	DrawDebugSphere(GetWorld(), GetActorLocation(), StopDistance, 15, FColor::Yellow, false);
	DrawDebugSphere(GetWorld(), GetActorLocation(), AttackRange, 15, FColor::Red, false);*/

	if (!IsValid(Target))
	{
		GetTargetInRange();
	}
	else
	{
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), Target->GetActorLocation(), CollisionChanel);

		if (!bHit)
			return;
		
		FVector DirectionToTarget = HitResult.ImpactPoint - GetActorLocation();

		if (DirectionToTarget.Length() > StopDistance)
			MoveToTarget(DirectionToTarget, DeltaTime);

		if (DirectionToTarget.Length() <= AttackRange)
			AttackTarget(DirectionToTarget, HitResult.ImpactPoint, DeltaTime);
	}
}

void AEnemyAI::GetTargetInRange()
{
	TArray<AActor*> TargetActors;

	GetActorsWithTag(TEXT("Home"), TargetActors);
	GetActorsWithTag(TEXT("Defense"), TargetActors);
	GetActorsWithTag(TEXT("Plant"), TargetActors);

	float MinDistance = std::numeric_limits<float>::max();
	AActor* CurrentTarget = nullptr;
	for (AActor* Actor : TargetActors)
	{
		float Distance = FVector::Distance(GetActorLocation(), Actor->GetActorLocation());
		if (Distance <= MinDistance)
		{
			MinDistance = Distance;
			CurrentTarget = Actor;
		}
	}

	if (CurrentTarget == nullptr)
		return;

	Target = CurrentTarget;
	UE_LOG(LogTemp, Warning, TEXT("Target %s"), *Target->GetName());

	if (Target->Tags.Contains("Home"))
	{
		CollisionChanel = ECollisionChannel::ECC_GameTraceChannel3;
	}
	else if (Target->Tags.Contains("Defense"))
	{
		CollisionChanel = ECollisionChannel::ECC_GameTraceChannel4;
	}
	else if (Target->Tags.Contains("Plant"))
	{
		CollisionChanel = ECollisionChannel::ECC_GameTraceChannel5;
	}
}

void AEnemyAI::GetActorsWithTag(FName Tag, TArray<AActor*>& OutTargetActors)
{
	TArray<AActor*> TempActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), Tag, TempActors);

	for (AActor* Actor : TempActors)
	{
		OutTargetActors.Add(Actor);
	}
}

void AEnemyAI::MoveToTarget(FVector DirectionToTarget, float DeltaTime)
{
	DirectionToTarget.Normalize();
	FVector MoveDirection = DirectionToTarget * MoveSpeed * DeltaTime;
	AddActorLocalOffset(MoveDirection, true);

	FRotator LookAtRotation = FRotator(0.0f, MoveDirection.Rotation().Yaw, 0.0f);
	Mesh->SetWorldRotation(FMath::RInterpTo(Mesh->GetComponentRotation(), LookAtRotation, DeltaTime, LookSpeed));
}

void AEnemyAI::AttackTarget(FVector DirectionToTarget, FVector HitPoint, float DeltaTime)
{
	if (CurrentAttackTime <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attacking"))
		Attack(Target);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), EnemyHitEffect, HitPoint);
		CurrentAttackTime = TimeBetweenAttacks;
	}
	else
	{
		CurrentAttackTime -= DeltaTime;
	}
}