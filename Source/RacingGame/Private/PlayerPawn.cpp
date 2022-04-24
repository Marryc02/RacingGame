// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(GetRootComponent());

	FloatingPawnMovementComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovementComp"));
	FloatingPawnMovementComp->Deceleration = 2000;
	FloatingPawnMovementComp->Acceleration = 2000;


	// Camera 1

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(false);

	SpringArm->SetRelativeRotation(FRotator(-25.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 600.f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 5.f;

	SpringArm->SetupAttachment(PlayerMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	

	// Camera 2

	SpringArm2 = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp2"));
	SpringArm2->bDoCollisionTest = false;
	SpringArm2->SetUsingAbsoluteRotation(false);

	SpringArm2->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	SpringArm2->TargetArmLength = -100.f;
	SpringArm2->bEnableCameraLag = false;
	SpringArm2->CameraLagSpeed = 5.f;

	SpringArm2->SetupAttachment(PlayerMesh);

	Camera2 = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera2"));
	Camera2->bUsePawnControlRotation = false;
	Camera2->SetupAttachment(SpringArm2, USpringArmComponent::SocketName);
	Camera2->AddLocalOffset(FVector(0.0f, 0.0f, 50.0f));

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	AddMovementInput(GetActorForwardVector(), 1.f);

	
	if (BoostActivated == true)
	{
		BoostDuration += DeltaTime;
		BoostLeft = 6.f - BoostDuration;
		if (BoostDuration > BoostLimit)
		{
			BoostActivated = false;
			FloatingPawnMovementComp->MaxSpeed = 1000.0f;
			BoostDuration = 0.f;
		}
	}
	
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent != nullptr);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("PauseGame", EInputEvent::IE_Pressed, this, &APlayerPawn::PauseGame).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("SwitchPerspective", EInputEvent::IE_Pressed, this, &APlayerPawn::SwitchPerspective);

	PlayerInputComponent->BindAction("AirBrakes", EInputEvent::IE_Pressed, this, &APlayerPawn::StartAirBrakes);
	PlayerInputComponent->BindAction("AirBrakes", EInputEvent::IE_Released, this, &APlayerPawn::StopAirBrakes);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &APlayerPawn::MoveLeftRight);
	PlayerInputComponent->BindAxis("MoveUpDown", this, &APlayerPawn::MoveUpDown);

	PlayerInputComponent->BindAction("BoostPower", EInputEvent::IE_Pressed, this, &APlayerPawn::BoostActivation);

}

void APlayerPawn::PauseGame() {
	if (isPaused == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("PAUSED"));
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("You have paused the game!")));
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		isPaused = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UNPAUSED"));
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Yellow, FString::Printf(TEXT("You have unpaused the game!")));
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		isPaused = false;
	}
}

void APlayerPawn::SwitchPerspective() {
	UE_LOG(LogTemp, Warning, TEXT("Switching perspective view"));

		if (firstPerson == false) {
			Camera->Deactivate();
			Camera2->Activate();

			firstPerson = true;
		}
		else {
			Camera->Activate();
			Camera2->Deactivate();

			firstPerson = false;
		}
}

void APlayerPawn::BoostActivation() {
	if (BoostActivated == false)
	{
		FloatingPawnMovementComp->MaxSpeed = 5000.0f;
		BoostActivated = true;
	}
}

void APlayerPawn::StartAirBrakes() {
	FloatingPawnMovementComp->MaxSpeed = 500.0f;
}

void APlayerPawn::StopAirBrakes() {
	FloatingPawnMovementComp->MaxSpeed = 1000.0f;
}

void APlayerPawn::MoveLeftRight(float Value) {
	LeftRightTurnSpeed = FMath::FInterpTo(LeftRightTurnSpeed, Value, GetWorld()->GetDeltaSeconds(), 1.f);
	AddActorLocalRotation(FRotator(0.f, 1.f, 0.f) * LeftRightTurnSpeed);
	PlayerMesh->USceneComponent::SetRelativeRotation(FRotator(0.f, 0.f, 40.f) * LeftRightTurnSpeed);
}

void APlayerPawn::MoveUpDown(float Value) {
	UpDownTurnSpeed = FMath::FInterpTo(UpDownTurnSpeed, Value, GetWorld()->GetDeltaSeconds(), 1.f);
	AddActorLocalRotation(FRotator(1.f, 0.f, 0.f) * UpDownTurnSpeed);
<<<<<<< Updated upstream
=======
}

void APlayerPawn::BoostActivation() {
	if (BoostActivated == false)
	{
		FloatingPawnMovementComp->MaxSpeed = 5000.0f;
		BoostActivated = true;
	}
}

void APlayerPawn::Shoot() {
	if (Ammo > 0) 
	{
		Ammo -= 1;

		UWorld* World = GetWorld();
		if (World)
		{
			FVector Location = GetActorLocation();
			World->SpawnActor<AActor>(BulletActorConnectionBP, Location + FVector(100.f, 0.f, 0.f), GetActorRotation());
			UGameplayStatics::PlaySound2D(World, ShootingSound, 1.f, 1.f, 0.f, 0);

		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Shooting"));

}

int APlayerPawn::RetMaxHealth()
{
	return MaxHealth;
}

int APlayerPawn::RetHealth()
{
	return Health;
}

int APlayerPawn::RetMaxBoost()
{
	return BoostLimit;
}

int APlayerPawn::RetBoost()
{
	return BoostLeft;
}

int APlayerPawn::RetMaxAmmo()
{
	return MaxAmmo;
}

int APlayerPawn::RetAmmo()
{
	return Ammo;
}

void APlayerPawn::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (OtherActor->IsA(AAmmoCrate::StaticClass()))
	//{
	//	Cast<AAmmoCrate>(OtherActor)->ImHit();

	//	Ammo = 30;
	//	SpawnCrate = true;
	//	UWorld* NewWorld = GetWorld();
	//	UGameplayStatics::PlaySound2D(NewWorld, ReloadingSound, 1.f, 1.f, 0.f, 0);
	//}

	//if (OtherActor->IsA(AEnemy::StaticClass()))
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Ship hit enemy"));
	//	GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("You were defeated by the invaders. Game over!"), Ammo));
	//	bEnemyDied = true;
	//	this->SetActorHiddenInGame(true);
	//	UGameplayStatics::SetGamePaused(GetWorld(), true);
	//}
	if (OtherActor->IsA(ATrackActor::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Ship hit the track."));
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("You crashed into the track!")));
		this->Destroy();
	}
>>>>>>> Stashed changes
}