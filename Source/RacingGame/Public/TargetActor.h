// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPawn.h"
#include "TargetActor.generated.h"


UCLASS()
class RACINGGAME_API ATargetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	class APlayerPawn* PlayerPawnPtr = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMesh")
		class UShapeComponent* CollisionBox = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMesh")
		class UStaticMeshComponent* PlayerMesh = nullptr;

	/*UFUNCTION(BlueprintCallable)
		int RetTargetsShot();*/

	UPROPERTY(EditAnywhere, Category = "Movement")
		float Speed = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float BoostLeft = 10.f;

	FVector InitialLocation;

	bool allTargetsDown = false;

private:

	FVector MoveDirection = FVector(0.f, 0.f, -1.f);

	float moveDuration = 0.f;
	bool moveDown = true;


	int TargetsShot = 0;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
