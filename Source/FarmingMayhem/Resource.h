// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Resource.generated.h"

UENUM(BlueprintType)
enum ResourceType
{
	Wood,
	Stone,
	Coin
};


UCLASS()
class FARMINGMAYHEM_API AResource : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleCollider;

	class UCellObject* CellUnder;

	UPROPERTY(EditAnywhere, Category = "Drop Amount", meta = (AllowPrivateAccess = "true"))
	int DropAmount;

public:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ResourceType> Type;

public:	
	// Sets default values for this actor's properties
	AResource();
	void Initialize(class UCellObject* SetCellUnder);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDamage();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
