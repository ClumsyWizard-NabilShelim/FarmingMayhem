// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedBuilding.h"
#include "Components/SphereComponent.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

ARangedBuilding::ARangedBuilding()
{
	DetectionCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Detection Collider"));
	DetectionCollider->SetupAttachment(RootComponent);

	RotateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rotate Mesh"));
	RotateMesh->SetupAttachment(RootComponent);

	ShootPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Shoot Point"));
	ShootPoint->SetupAttachment(RotateMesh);
}

void ARangedBuilding::BeginPlay()
{
	Super::BeginPlay();
	DetectionCollider->OnComponentBeginOverlap.AddDynamic(this, &ARangedBuilding::OnTargetEnter);
	DetectionCollider->OnComponentEndOverlap.AddDynamic(this, &ARangedBuilding::OnTargetExit);
}

void ARangedBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsActive)
		return;

	if (!IsValid(Target))
	{
		GetTargetInRange();
	}
	else
	{
		FVector DirectionToTarget = Target->GetActorLocation() - RotateMesh->GetComponentLocation();
		RotateMesh->SetWorldRotation(FMath::RInterpTo(RotateMesh->GetComponentRotation(), DirectionToTarget.Rotation(), DeltaTime, RotateSpeed));

		if (CurrentAttackTime <= 0)
		{
			AttackTarget();
			CurrentAttackTime = TimeBetweenAttacks;
		}
		else
		{
			CurrentAttackTime -= DeltaTime;
		}
	}
}

void ARangedBuilding::OnTargetEnter(UPrimitiveComponent* OverlappedComponent, AActor* OverlapActor, UPrimitiveComponent* OverlapActorComp, int32 BodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (TargetsInRange.Contains(OverlapActor))
		return;

	TargetsInRange.Add(OverlapActor);
}

void ARangedBuilding::OnTargetExit(UPrimitiveComponent* OverlappedComponent, AActor* OverlapActor, UPrimitiveComponent* OverlapComp, int32 BodyIndex)
{
	if (!TargetsInRange.Contains(OverlapActor))
		return;

	TargetsInRange.Remove(OverlapActor);
	if (OverlapActor == Target)
		Target = nullptr;
}

void ARangedBuilding::GetTargetInRange()
{
	DetectionCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DetectionCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	if (TargetsInRange.Num() == 0)
		return;

	if (TargetsInRange.Num() == 1)
	{
		Target = TargetsInRange[0];
		return;
	}

	float MinDistance = std::numeric_limits<float>::max();
	AActor* CurrentTarget = nullptr;
	for (AActor* Actor : TargetsInRange)
	{
		float Distance = FVector::Distance(GetActorLocation(), Actor->GetActorLocation());
		if (Distance <= MinDistance)
		{
			MinDistance = Distance;
			CurrentTarget = Actor;
		}
	}

	Target = CurrentTarget;
}

void ARangedBuilding::AttackTarget()
{
	if (AttackSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), AttackSound);
	}

	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ShootPoint->GetComponentLocation(), ShootPoint->GetComponentRotation());
}
