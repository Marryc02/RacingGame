// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointActor.h"
#include "Components/BoxComponent.h"
#include "PlayerPawn.h"
#include "StartLineActor.h"

// Sets default values
ACheckpointActor::ACheckpointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);

}

// Called when the game starts or when spawned
void ACheckpointActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (checkpointHidden == true)
	{
		ACheckpointActor::SetActorEnableCollision(false);
		HideDuration += DeltaTime;
		if (HideDuration > HideLimit)
		{
			checkpointHidden = false;
			ACheckpointActor::SetActorEnableCollision(true);
			HideDuration = 0.f;
		}
	}
}

