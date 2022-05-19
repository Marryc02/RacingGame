// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATargetActor::ATargetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ATargetActor::BeginPlay()
{
	Super::BeginPlay();
	
	InitialLocation = GetActorLocation();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATargetActor::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CollisionBox not found!"));
	}
}

// Called every frame
void ATargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerPawnPtr == nullptr)
	{
		PlayerPawnPtr = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	}

	if (moveDown == true)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += (MoveDirection * Speed * DeltaTime);
		SetActorLocation(NewLocation);

		if (NewLocation.Z < InitialLocation.Z-5999.f)
		{
			MoveDirection = FVector(0.f, 0.f, 1.f);
			moveDown = false;
			UE_LOG(LogTemp, Warning, TEXT("Targets moving up."));
		}
	}
	else if (moveDown == false)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += (MoveDirection * Speed * DeltaTime);
		SetActorLocation(NewLocation);

		if (NewLocation.Z > InitialLocation.Z - 1.f)
		{
			MoveDirection = FVector(0.f, 0.f, -1.f);
			moveDown = true;
			UE_LOG(LogTemp, Warning, TEXT("Targets moving down."));
		}
	}
	
	if (PlayerPawnPtr != nullptr)
	{
		if (TargetsShot == 9)
		{
			PlayerPawnPtr->allTargetsDown = true;
		}
	}

}

void ATargetActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PlayerPawnPtr == nullptr)
	{
		PlayerPawnPtr = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	}

	if (OtherActor->IsA(ABulletActor::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("BULLET"));
		UWorld* World = GetWorld();
		if (World) {
			if (PlayerPawnPtr != nullptr)
			{
				PlayerPawnPtr->TargetsShotCount++;
			}
			TargetsShot++;

			this->Destroy();
		}
	}

	else if (OtherActor->IsA(APlayerPawn::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("PLAYER"));
		
		if (PlayerPawnPtr != nullptr)
		{
			PlayerPawnPtr->TargetsShotCount++;
			PlayerPawnPtr->Health--;
		}
		TargetsShot++;

		this->Destroy();

	}
}