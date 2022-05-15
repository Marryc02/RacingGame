// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "../RacingGameGameModeBase.h"
#include "RacingGameClasses.h"
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


	// On startup
	
	class ARacingGameGameModeBase* GameModeBasePtrs = Cast<ARacingGameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	FTimerHandle StartTimer;

	UFUNCTION()
		void OnStartTimerComplete();

	bool gameHasStarted = false;


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
		float BoostLimit = 10.f;

	UPROPERTY(EditAnywhere, Category = "BoostTime")
		float BoostDuration = 0.f;

	UPROPERTY(EditAnywhere, Category = "BoostTime")
		float BoostLeft = 10.f;

	bool boostAvailable = false;


	// HUD Widget

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> HUDWidgetClass;

	class UHUDWidget_UI* HUDWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		bool bRaceFinished = false;

	// Health

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMesh")
		int Health = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMesh")
		int MaxHealth = 5;


	// Shooting

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> BulletActorConnectionBP;


	// EndGame Widget

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> EndGameWidgetClass;

	UFUNCTION(BlueprintCallable)
		void CreateEndGameWidget();

	// Return varibles

	UFUNCTION(BlueprintCallable)
		int RetMaxHealth();
	UFUNCTION(BlueprintCallable)
		int RetHealth();

	UFUNCTION(BlueprintCallable)
		int RetMaxBoost();
	UFUNCTION(BlueprintCallable)
		int RetBoost();

	UFUNCTION(BlueprintCallable)
		int RetLaps();


	// Start line and checkpoints

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMesh")
		int FinishLineCrossed = 0;


	// Audio

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAudio")
		USoundBase* ShootingSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAudio")
		USoundBase* DeathSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAudio")
		USoundBase* BoostSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAudio")
		USoundBase* FuelPickUpSound = nullptr;


	// Effects

	UPROPERTY(EditAnywhere, Category = "PlayerEffects")
		UParticleSystem* PlayerExplosion = nullptr;


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