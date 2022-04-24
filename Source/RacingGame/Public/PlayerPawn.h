// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPawn.generated.h"

UCLASS()
class RACINGGAME_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Other


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMesh")
		class UShapeComponent* CollisionBox = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMesh")
		class UStaticMeshComponent* PlayerMesh = nullptr;


	// Cameras


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cameras")
		class USpringArmComponent* SpringArm {
		nullptr
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cameras")
		class UCameraComponent* Camera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cameras")
		class USpringArmComponent* SpringArm2 {
		nullptr
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cameras")
		class UCameraComponent* Camera2 = nullptr;


	// Movement


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		class UFloatingPawnMovement* FloatingPawnMovementComp = nullptr;


	UPROPERTY(EditAnywhere, Category = "BoostTime")
		float BoostLimit = 5.f;

	UPROPERTY(EditAnywhere, Category = "BoostTime")
		float BoostDuration = 0.f;


	// Shooting


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMesh")
		int Ammo = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMesh")
		int MaxAmmo = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMesh")
		USoundBase* ShootingSound = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> BulletActorConnectionBP;

	UFUNCTION(BlueprintCallable)
		int RetMaxAmmo();

	UFUNCTION(BlueprintCallable)
		int RetAmmo();


private:

	bool isPaused = false;
	void PauseGame();

	bool firstPerson = false;
	void SwitchPerspective();

	float LeftRightTurnSpeed = 0.f;
	float UpDownTurnSpeed = 0.f;

	void StartAirBrakes();
	void StopAirBrakes();
	void MoveLeftRight(float Value);
	void MoveUpDown(float value);

	bool BoostActivated = false;
	void BoostActivation();

	void Shoot();


	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};