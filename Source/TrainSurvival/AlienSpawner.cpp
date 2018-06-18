// Fill out your copyright notice in the Description page of Project Settings.

#include "AlienSpawner.h"
#include "Engine.h"
#include "Alien.h"


// Sets default values
AAlienSpawner::AAlienSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAlienSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAlienSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Always add delta time to our Spawn Time
	SpawnTime += DeltaTime;

	bool bShouldSpawn = (SpawnTime > SpawnDelay);

	if (bShouldSpawn)
	{
		//Deduct spawn delay from accumulated time value
		SpawnTime -= SpawnDelay;
		SpawnDelay = GetRandomSpawnDelay();

		FVector Location = GetActorLocation();
		GetWorld()->SpawnActor<AAlien>(LitenAlien, Location, FRotator::ZeroRotator);
	}
}

float AAlienSpawner::GetRandomSpawnDelay()
{
	// Get a random float that falls within the spawn delay range
	return FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
}

