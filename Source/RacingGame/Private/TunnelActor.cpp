// Fill out your copyright notice in the Description page of Project Settings.


#include "TunnelActor.h"

// Sets default values
ATunnelActor::ATunnelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));

}

// Called when the game starts or when spawned
void ATunnelActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATunnelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

