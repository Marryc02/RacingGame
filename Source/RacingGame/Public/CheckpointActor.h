// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPawn.h"
#include "StartLineActor.h"
#include "CheckpointActor.generated.h"

UCLASS()
class RACINGGAME_API ACheckpointActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpointActor();

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


private:

	bool checkpointHidden = false;

	float HideDuration = 0.f;
	float HideLimit = 30.0f;


	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};