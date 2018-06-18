// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemOne.h"



// Sets default values
AItemOne::AItemOne()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);

	BoxComponent->bGenerateOverlapEvents = true;

}

// Called when the game starts or when spawned
void AItemOne::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AItemOne::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (pickedUp)
	{
		SetActorLocation(FVector(myOwner->GetActorLocation().X, myOwner->GetActorLocation().Y, myOwner->GetActorLocation().Z + 10));
	}
}

void AItemOne::pickUp(AActor * Owner)
{
	pickedUp = true;
	myOwner = Owner;
	BoxComponent->SetEnableGravity(false);
}

void AItemOne::throwAway()
{
	pickedUp = false;
	myOwner = nullptr;
	BoxComponent->SetEnableGravity(true);
	BoxComponent->AddForce(FVector(10000000, 0, 0));
}

UStaticMeshComponent* AItemOne::getMeshComp()
{
	return OurVisibleComponent;
}


