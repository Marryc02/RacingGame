// Fill out your copyright notice in the Description page of Project Settings.


#include "FuelActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraModifier.h"

// Sets default values
AFuelActor::AFuelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AFuelActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AFuelActor::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CollisionBox not found!"));
	}

	BoostCameraModifier = UGameplayStatics::GetPlayerCameraManager(this, 0)->AddNewCameraModifier(BoostCameraModifierClass);
	BoostCameraModifier->DisableModifier(true);

}

// Called every frame
void AFuelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (fuelActorHidden == true)
	{
		HideDuration += DeltaTime;
		if (HideDuration > HideLimit)
		{
			fuelActorHidden = false;
			AFuelActor::SetActorHiddenInGame(false);
			AFuelActor::SetActorEnableCollision(true);
		}
	}

	if (BoostEffectLimit)
	{
		BoostEffectDuration += DeltaTime;
		if (BoostEffectDuration > BoostEffectLimit)
		{
			BoostEffectLimit = false;
			BoostCameraModifier->DisableModifier(true);
		}
	}
}

void AFuelActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerPawn::StaticClass()) && fuelActorHidden == false)
	{
		APlayerPawn* PlayerPawnPtr = Cast<APlayerPawn>(OtherActor);

		UWorld* World = GetWorld();
		if (World) {

			PlayerPawnPtr->boostAvailable = true;
			fuelActorHidden = true;
			UGameplayStatics::PlaySound2D(World, FuelPickUpSound, 1.f, 1.f, 0.f, 0);

			// Camera Modifier

			BoostEffectUsed = true;
			
			BoostCameraModifier->EnableModifier();

			AFuelActor::SetActorHiddenInGame(true);
			AFuelActor::SetActorEnableCollision(false);

			GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("Player picked up fuel!")));
		}
	}

}
