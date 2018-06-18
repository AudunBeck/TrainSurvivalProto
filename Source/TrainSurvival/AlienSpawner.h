// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AlienSpawner.generated.h"

UCLASS()
class TRAINSURVIVAL_API AAlienSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlienSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Spawning)
		TSubclassOf<class AAlien> LitenAlien;

	/** Minimum spawn delay*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		float SpawnDelayRangeLow = 1.0f;

	/** Maximum spawn delay */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		float SpawnDelayRangeHigh = 5.0f;

	/** Whether or not spawning is enabled */
	bool bSpawningEnabled;

	/** Calculates a random spawn delay */
	float GetRandomSpawnDelay();

	/** The current spawn delay */
	float SpawnDelay;

	/** The timer for when to spawn the pickup */
	float SpawnTime;
	
};
