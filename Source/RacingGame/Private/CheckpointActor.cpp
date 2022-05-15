// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACheckpointActor::ACheckpointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ACheckpointActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointActor::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CollisionBox not found!"));
	}
}

// Called every frame
void ACheckpointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (checkpointHidden == true)
	{
		HideDuration += DeltaTime;
		if (HideDuration > HideLimit)
		{
			checkpointHidden = false;
		}
	}
}

void ACheckpointActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerPawn::StaticClass()) && checkpointHidden == false)
	{
		AStartLineActor* StartLinePtr = Cast<AStartLineActor>(OtherActor);

		checkpointHidden = true;
		StartLinePtr->CheckpointsReached += 1;

		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Yellow, FString::Printf(TEXT("Player reached a checkpoint!")));
	}

}

