// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerChar.h"
#include "Components/InputComponent.h"
#include "Engine.h"


// Sets default values
APlayerChar::APlayerChar()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);

	SphereComponent->bGenerateOverlapEvents = true;
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayerChar::OnOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &APlayerChar::EndOnOverlap);

}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isPickedUp)
	{
		SetActorLocation(FVector(myOwner->GetActorLocation().X, myOwner->GetActorLocation().Y, myOwner->GetActorLocation().Z + 300));
	}

}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move_Y", this, &APlayerChar::MoveForward);
	PlayerInputComponent->BindAxis("Move_X", this, &APlayerChar::MoveRight);
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &APlayerChar::PickUp);
	PlayerInputComponent->BindAction("UseItem", IE_Pressed, this, &APlayerChar::UseItem);

}

void APlayerChar::MoveForward(float amount)
{
	if (Controller && amount && !isPickedUp)
	{

		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw + ExtraRotation, 0); //ExtraRotation is added to the player's controls changes, 
																		//found this easier than other methods since it just adds a float value, and can be changed into any direction.

																		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, amount);
	}
}


void APlayerChar::MoveRight(float amount)
{
	if (Controller && amount && !isPickedUp)
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw + ExtraRotation, 0);
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, amount);
	}
}

void APlayerChar::PickUp()
{
	if (!holdingSomething && onItem && Item != nullptr)
	{
		holdingSomething = true;
		Item->pickUp(this);
		whatItem = 1;
	}
	else if (holdingSomething && Item != nullptr)
	{
		holdingSomething = false;
		Item->throwAway();
		Item = nullptr;
		whatItem = 0;
	}

	if (!holdingSomething && onPlayer && PickedPlayer != nullptr)
	{
		holdingSomething = true;
		PickedPlayer->IsCarried(true, this);
		whatItem = 2;
	}

	else if (holdingSomething && PickedPlayer!= nullptr)
	{
		holdingSomething = false;
		PickedPlayer->IsCarried(false, nullptr);
		Item = nullptr;
		whatItem = 0;
	}

	if (!holdingSomething && punchableFace != nullptr)
	{
		holdingSomething = true;
		punchableFace->IsCarried(true, this);
		whatItem = 3;
	}

	else if (holdingSomething && punchableFace != nullptr)
	{
		holdingSomething = false;
		punchableFace->IsCarried(false, nullptr);
		punchableFace = nullptr;
		whatItem = 0;
	}
}

void APlayerChar::UseItem()
{
	if (whatItem == 1 && punchableFace != nullptr)
	{
		punchableFace->Destroy();
	}
		
}

void APlayerChar::IsCarried(bool carried, APlayerChar* Carry)
{
	isPickedUp = carried;
	myOwner = Carry;
	if (!carried)
	{
		GetCapsuleComponent()->AddForce(FVector(100000, 0, 0));
	}
}

void APlayerChar::OnOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA(AItemOne::StaticClass()) && !holdingSomething)
	{
		Item = Cast<AItemOne>(OtherActor);
		onItem = true;
	}
	else if (OtherActor->IsA(APlayerChar::StaticClass()) && OtherActor != this && !holdingSomething)
	{
		PickedPlayer = Cast<APlayerChar>(OtherActor);
		onPlayer = true;
	}

	if (OtherActor->IsA(AAlien::StaticClass()))
	{
		punchableFace = Cast<AAlien>(OtherActor);
	}
}

void APlayerChar::EndOnOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AItemOne::StaticClass()) && !holdingSomething)
	{
		Item = nullptr;
		onItem = false;
	}

	if (OtherActor->IsA(APlayerChar::StaticClass()) && !holdingSomething)
	{
		PickedPlayer = nullptr;
		onPlayer = false;
	}
	
	if (OtherActor->IsA(AAlien::StaticClass()))
	{
		punchableFace = nullptr;
	}

}

