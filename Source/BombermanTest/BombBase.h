// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BombBase.generated.h"

UCLASS()
class BOMBERMANTEST_API ABombBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABombBase();

	UFUNCTION(BlueprintCallable)
	TArray<FVector> LinetraceBombExplosion(FVector direction, float range, float tileSize = 50, ECollisionChannel collisionChannel = ECC_Visibility);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
