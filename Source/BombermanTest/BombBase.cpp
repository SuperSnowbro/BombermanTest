// Fill out your copyright notice in the Description page of Project Settings.

#include "BombBase.h"
#include "IBombRaycastTargetable.h"

// Sets default values
ABombBase::ABombBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABombBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABombBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// checks {range} tiles in the given direction (called once per direction) and returns an array of valid explosion tile positions.
// currently uses the Visibility channel.
TArray<FVector> ABombBase::LinetraceBombExplosion(FVector direction, float range, float tileSize, ECollisionChannel collisionChannel)
{
	TArray<FVector> result;
	UWorld* world = GetWorld();
	if (ensureMsgf(world != nullptr, TEXT("World is invalid")))
	{
		FHitResult outHit;
		FVector displacement = direction * range * tileSize;
		FVector location = GetActorLocation();
		int numberOfTiles; //the number of valid tiles in the given direction that the raycast operation will yield
		FCollisionQueryParams params; //extra params in case of need!
		params.AddIgnoredActor(this);
		if (world->LineTraceSingleByChannel(outHit, location, location + displacement, collisionChannel, params))
		{
			AActor* target = outHit.Actor.Get();
			if (target && target->Implements<UBombRaycastTargetable>()) //if the target is susceptible to bomb (like destructible walls), we notify him that the bomb explosion hit him!
			{
				IBombRaycastTargetable::Execute_NotifyBombRaycastHit(target);
			}
			numberOfTiles = FMath::FloorToInt(outHit.Time * range); //this magical calculation allows us to discern the number of free tiles without scratching our head too much!
		}
		else
		{
			numberOfTiles = range; //if nothing was hit, it means that all the tiles in range were free
		}

		for (int i = 1; i <= numberOfTiles; ++i)
		{
			result.Add(i * direction * tileSize); //we populate the array of valid position based on the free tiles detected (between 0 and {range})
		}
	}
	return result;
}