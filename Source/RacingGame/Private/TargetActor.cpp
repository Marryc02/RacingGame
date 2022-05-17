// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetActor.h"

// Sets default values
ATargetActor::ATargetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATargetActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATargetActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ABulletActor::StaticClass()))
	{
		UWorld* World = GetWorld();
		if (World) {
			TargetsShot++;

			this->Destroy();
		}
	}
}

int ATargetActor::RetTargetsShot()
{
	return TargetsShot;
}
