// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

UCLASS()
class RACINGGAME_API ABulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletMesh")
		UShapeComponent* CollisionBox = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMesh")
		class UStaticMeshComponent* PlayerMesh = nullptr;

private:

	UPROPERTY(EditAnywhere, Category = "BulletThings")
		float Speed = 5000.0f;

	UPROPERTY(EditAnywhere, Category = "BulletThings")
		float TimeBeforeDestroy = 30.0f;

	UPROPERTY(EditAnywhere, Category = "BulletThings")
		float TimeLived = 0.f;

	UPROPERTY(EditAnywhere, Category = "BulletThings")
		UParticleSystem* BulletFireFX = nullptr;

	UPROPERTY(EditAnywhere, Category = "BulletThings")
		USoundBase* BulletFireSound = nullptr;

};
