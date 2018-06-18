// Fill out your copyright notice in the Description page of Project Settings.

#include "Alien.h"
#include "Engine.h"


// Sets default values
AAlien::AAlien()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAlien::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAlien::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isPickedUp)
	{
		// Finds all instances of Liv, and sets the "LivReference" to the first ([0]) actor found
		TArray<AActor*> FoundActors;
		APlayerChar* PlayerRef = nullptr;
		if (PlayerRef == nullptr)
		{
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerChar::StaticClass(), FoundActors);
			PlayerRef = Cast<APlayerChar>(FoundActors[0]);
		}

		FVector NewLocation = GetActorLocation();
		FVector PlayerLoc = PlayerRef->GetActorLocation();

		NewLocation += (MoveDirection * Speed * DeltaTime);
		SetActorLocation(NewLocation);
		MoveDirection = PlayerRef->GetActorLocation() - GetActorLocation();
		MoveDirection.Normalize();
	}

	else if (isPickedUp)
	{
		SetActorLocation(FVector(myOwner->GetActorLocation().X, myOwner->GetActorLocation().Y, myOwner->GetActorLocation().Z + 300));
	}
}

void AAlien::IsCarried(bool carried, APlayerChar * Carry)
{
	isPickedUp = carried;
	myOwner = Carry;
}


