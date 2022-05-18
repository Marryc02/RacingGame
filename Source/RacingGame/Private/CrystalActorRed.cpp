// Fill out your copyright notice in the Description page of Project Settings.


#include "CrystalActorRed.h"

// Sets default values
ACrystalActorRed::ACrystalActorRed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));

}

// Called when the game starts or when spawned
void ACrystalActorRed::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACrystalActorRed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

