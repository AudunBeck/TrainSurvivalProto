// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrainSurvival.h"
#include "Alien.generated.h"

UCLASS()
class TRAINSURVIVAL_API AAlien : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlien();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Defines visible properties for
	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;

	// Defines direction for 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector MoveDirection;

	// Sets the movement speed of Aliens
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed = 150.f;

	UPROPERTY(EditAnywhere)
		bool isPickedUp = false;

		class APlayerChar* myOwner = nullptr;

	void IsCarried(bool carried, APlayerChar* Carry);

	
};
