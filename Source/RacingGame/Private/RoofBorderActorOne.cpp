// Fill out your copyright notice in the Description page of Project Settings.


#include "RoofBorderActorOne.h"
#include "Components/BoxComponent.h"

// Sets default values
ARoofBorderActorOne::ARoofBorderActorOne()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);
}

// Called when the game starts or when spawned
void ARoofBorderActorOne::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoofBorderActorOne::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

