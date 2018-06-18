// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ItemOne.h"
#include "TrainSurvival.h" //Did like this because circular dependencies is bad.
#include "PlayerChar.generated.h"

UCLASS()
class TRAINSURVIVAL_API APlayerChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float amount);
	void MoveRight(float amount);
	void PickUp();
	void UseItem();

	void IsCarried(bool carried, APlayerChar* Carry);

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
		void EndOnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
		AItemOne* Item = nullptr;

	UPROPERTY(EditAnywhere)
		int whatItem = 0;

	UPROPERTY(EditAnywhere)
		APlayerChar* PickedPlayer = nullptr;

	UPROPERTY(EditAnywhere)
		APlayerChar* myOwner = nullptr;
	
	UPROPERTY(EditAnywhere)
		class AAlien* punchableFace = nullptr; //Had to write class first, so it would pass the compiler boss.


		bool onItem = false;

		bool onPlayer = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AnimationVariables)
		bool holdingSomething = false;


	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category=AnimationVariables)
		bool isPickedUp = false;

	UPROPERTY(VisibleAnywhere)
		USphereComponent* SphereComponent;

	float ExtraRotation = 0;



};
