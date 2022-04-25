// Fill out your copyright notice in the Description page of Project Settings.


#include "StartLineActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AStartLineActor::AStartLineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	/*CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);*/
	SetRootComponent(CollisionBox);

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AStartLineActor::BeginPlay()
{
	Super::BeginPlay();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AStartLineActor::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CollisionBox not found!"));
	}
	
}

// Called every frame
void AStartLineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (startLineHidden == true)
	{
		HideDuration += DeltaTime;
		if (HideDuration > HideLimit)
		{
			startLineHidden = false;
		}
	}

}

void AStartLineActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerPawn::StaticClass()) && startLineHidden == false /*&& CheckpointsReached = 3*/)
	{
		APlayerPawn* PlayerPawnPtr = Cast<APlayerPawn>(OtherActor);

		startLineHidden = true;
		PlayerPawnPtr->FinishLineCrossed += 1;

		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("Player crossed the starting line!")));
	}

}


