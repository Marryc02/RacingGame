// Fill out your copyright notice in the Description page of Project Settings.


#include "StartLineActor.h"
#include "Components/BoxComponent.h"
#include "PlayerPawn.h"

// Sets default values
AStartLineActor::AStartLineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	/*CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);*/
	SetRootComponent(CollisionBox);

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
			HideDuration = 0.f;
		}
	}

}

void AStartLineActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerPawn::StaticClass()) && startLineHidden == false)
	{
		APlayerPawn* PlayerPawnPtr = Cast<APlayerPawn>(OtherActor);
		if (PlayerPawnPtr->allTargetsDown == true && PlayerPawnPtr->CheckpointsReached == 3)
		{
			UE_LOG(LogTemp, Warning, TEXT("Race finished."));
			PlayerPawnPtr->CreateEndGameWidget();
			GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("You won the race!")));
		}
		else
		{
			PlayerPawnPtr->RespawnLocation = GetActorLocation();
			if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "ShootingLevel")
			{
				PlayerPawnPtr->RespawnRotation = GetActorRotation() += FRotator(0.f, 90.f, 0.f);
			}
			else if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "RacingLevel")
			{
				PlayerPawnPtr->RespawnRotation = GetActorRotation() += FRotator(0.f, -90.f, 0.f);
			}

			if (PlayerPawnPtr->CheckpointsReached == 3)
			{
				startLineHidden = true;
				PlayerPawnPtr->FinishLineCrossed += 1;
				PlayerPawnPtr->CheckpointsReached = 0;

				if (PlayerPawnPtr->FinishLineCrossed < 3) {
					GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("Player crossed the starting line!")));
				}
				else if (PlayerPawnPtr->FinishLineCrossed == 3) {
					UE_LOG(LogTemp, Warning, TEXT("Race finished."));
					PlayerPawnPtr->CreateEndGameWidget();
					GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("You won the race!")));
				}
			}
		}
	}
}



