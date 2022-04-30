// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CheckpointBalloonsActor.h"

// Sets default values
ACheckpointBalloonsActor::ACheckpointBalloonsActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ACheckpointBalloonsActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpointBalloonsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

