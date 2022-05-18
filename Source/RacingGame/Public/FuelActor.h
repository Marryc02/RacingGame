// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPawn.h"
#include "FuelActor.generated.h"

UCLASS()
class RACINGGAME_API AFuelActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFuelActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMesh")
		class UShapeComponent* CollisionBox = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMesh")
		class UStaticMeshComponent* PlayerMesh = nullptr;


	// Audio

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAudio")
		USoundBase* FuelPickUpSound = nullptr;


	// Camera Modifier

	UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere, Category = "CameraBoost")
		TSubclassOf<UCameraModifier> BoostCameraModifierClass = nullptr;

	UPROPERTY()
		class UCameraModifier* BoostCameraModifier = nullptr;


	// OnOverlap

	UPROPERTY(EditAnywhere, Category = "BoostTime")
		float BoostEffectLimit = 10.f;

	UPROPERTY(EditAnywhere, Category = "BoostTime")
		float BoostEffectDuration = 0.f;

	bool BoostEffectUsed = false;
	

private:

	bool fuelActorHidden = false;

	float HideDuration = 0.f;
	float HideLimit = 10.0f;


	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
