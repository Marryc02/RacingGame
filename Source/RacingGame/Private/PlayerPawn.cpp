	// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraModifier.h"
#include "Kismet/GameplayStatics.h"
#include "TrackActor.h"
#include "TunnelActor.h"
#include "StartLineActor.h"
#include "StartLineIndicatorColliderActor.h"
#include "CrystalActor.h"
#include "CrystalActorRed.h"
#include "RoofBorderActorOne.h"
#include "RoofBorderActorTwo.h"
#include "RegularBorderActor.h"
#include "CheckpointActor.h"
#include "TargetActor.h"
#include "HUDWidget_UI.h"
#include "EndGameUI.h"
#include "BorderWarning_UI.h"
#include "TargetsShotCounter_UI.h"
#include "GameOver_UI.h"



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
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 0.1f;
	SpringArm->CameraLagMaxDistance = 150.f;

	SpringArm->SetupAttachment(CollisionBox);

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

	SpringArm2->SetupAttachment(CollisionBox);

	Camera2 = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera2"));
	Camera2->bUsePawnControlRotation = false;
	Camera2->SetupAttachment(SpringArm2, USpringArmComponent::SocketName);
	Camera2->AddLocalOffset(FVector(0.0f, 0.0f, 50.0f));

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	// Other

	RespawnLocation = GetActorLocation();
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "ShootingLevel")
	{
		RespawnRotation = GetActorRotation() += FRotator(0.f, 90.f, 0.f);
	}
	else if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "RacingLevel")
	{
		RespawnRotation = GetActorRotation() += FRotator(0.f, -90.f, 0.f);
	}


	// Related to 3 2 1 GO!

	APlayerController* PlayerController = GetWorld()->GetFirstLocalPlayerFromController()->GetPlayerController(GetWorld());
	FInputModeUIOnly InputMode{};
	PlayerController->SetInputMode(InputMode);

	GetWorld()->GetTimerManager().SetTimer(StartTimer, this, &APlayerPawn::OnStartTimerComplete, 3.f, false);

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerPawn::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CollisionBox not found!"));
	}


	// HUD-Widget

	HUDWidget = CreateWidget<UHUDWidget_UI>(PlayerController, HUDWidgetClass.Get());
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HUDWidget not found!"));
	}

	// Targets Shot Widget

	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "ShootingLevel")
	{
		TargetsCounterWidget = CreateWidget<UTargetsShotCounter_UI>(PlayerController, TargetsCounterWidgetClass);
		if (TargetsCounterWidget)
		{
			TargetsCounterWidget->AddToViewport();
		}
	}


	// Camera Modifier

	BoostCameraModifier = UGameplayStatics::GetPlayerCameraManager(this, 0)->AddNewCameraModifier(BoostCameraModifierClass);
	BoostCameraModifier->DisableModifier(true);

}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Movement tick

	if (gameHasStarted == true && playerCrashed != true)
	{
		AddMovementInput(GetActorForwardVector(), 1.0f);
	}

	//Boost tick

	if (BoostActivated == true)
	{
		BoostDuration += DeltaTime;
		BoostCameraModifier->EnableModifier();
		if (BoostDuration > BoostLimit)
		{
			BoostActivated = false;
			FloatingPawnMovementComp->MaxSpeed = 6000.0f;
			BoostDuration = 0.f;
			BoostCameraModifier->DisableModifier(true);
		}
	}

	//Border tick

	if (RoofBorderTouched == true)
	{
		BorderSlowDuration += DeltaTime;
		if (BorderSlowDuration > BorderSlowLimit)
		{
			RoofBorderTouched = false;
			FloatingPawnMovementComp->MaxSpeed = 6000.0f;
			BorderSlowDuration = 0.f;

			UE_LOG(LogTemp, Warning, TEXT("WarningWidget collapsed"));
			WarningWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	//Respawn tick 

	if (playerCrashed == true)
	{
		respawnWait += DeltaTime;
		if (respawnWait > respawnWaitLimit)
		{
			playerCrashed = false;
			respawnWait = 0.f;

			if (Health > 0)
			{
				SetActorLocation(RespawnLocation);
				SetActorRotation(RespawnRotation);
				CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			}
			else
			{
				CreateGameOverWidget();
				this->Destroy();
			}
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
	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &APlayerPawn::Shoot);

}

//Start timer

void APlayerPawn::OnStartTimerComplete()
{
	APlayerController* PlayerController = GetWorld()->GetFirstLocalPlayerFromController()->GetPlayerController(GetWorld());
	FInputModeGameAndUI InputMode{};
	PlayerController->SetInputMode(InputMode);
	gameHasStarted = true;
	FloatingPawnMovementComp->MaxSpeed = 6000.0f;
}


// Pausing

void APlayerPawn::PauseGame() {
	if (isPaused == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("PAUSED"));
		/*GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("You have paused the game!")));*/
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		isPaused = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UNPAUSED"));
		/*GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Yellow, FString::Printf(TEXT("You have unpaused the game!")));*/
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		isPaused = false;
	}
}

// 3rd person

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


// Movement

void APlayerPawn::StartAirBrakes() {
	FloatingPawnMovementComp->MaxSpeed = 3000.0f;
}

void APlayerPawn::StopAirBrakes() {
	FloatingPawnMovementComp->MaxSpeed = 6000.0f;
}

void APlayerPawn::MoveLeftRight(float Value) {
	LeftRightTurnSpeed = FMath::FInterpTo(LeftRightTurnSpeed, Value, GetWorld()->GetDeltaSeconds(), 1.f);
	AddActorLocalRotation(FRotator(0.f, 1.f, 0.f) * LeftRightTurnSpeed);
	PlayerMesh->USceneComponent::SetRelativeRotation(FRotator(0.f, 0.f, 40.f) * LeftRightTurnSpeed);
}

void APlayerPawn::MoveUpDown(float Value) {
	UpDownTurnSpeed = FMath::FInterpTo(UpDownTurnSpeed, Value, GetWorld()->GetDeltaSeconds(), 1.f);
	AddActorLocalRotation(FRotator(1.f, 0.f, 0.f) * UpDownTurnSpeed);
}

void APlayerPawn::BoostActivation() {
	if (BoostActivated == false && boostAvailable == true)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FloatingPawnMovementComp->MaxSpeed = 10000.0f;
			UGameplayStatics::PlaySound2D(World, BoostSound, 1.f, 1.f, 0.f, 0);
			BoostActivated = true;
			boostAvailable = false;
		}
	}
}


// Shooting

void APlayerPawn::Shoot() {
		if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "ShootingLevel" && BoostActivated == false)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				FVector Location = GetActorLocation();
				World->SpawnActor<AActor>(BulletActorConnectionBP, Location + FVector(50.f, 0.f, 0.f), GetActorRotation());
				UGameplayStatics::PlaySound2D(World, ShootingSound, 1.f, 1.f, 0.f, 0);

			}

			UE_LOG(LogTemp, Warning, TEXT("Shooting"));
		}
	
}


// Return varibles

void APlayerPawn::CreateGameOverWidget()
{
	APlayerController* PlayerController = GetWorld()->GetFirstLocalPlayerFromController()->GetPlayerController(GetWorld());
	if (PlayerController)
	{
		if (HUDWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("HUDWidget collapsed"));
			HUDWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("HUDWidget not found!"));
		}

		if (TargetsCounterWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("TargetsCounterWidget collapsed"));
			TargetsCounterWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("TargetsCounterWidget not found!"));
		}

		UGameOver_UI* GameOverWidget = CreateWidget<UGameOver_UI>(PlayerController, GameOverWidgetClass);
		if (GameOverWidget)
		{
			GameOverWidget->AddToViewport();
			PlayerController->SetShowMouseCursor(true);
			FInputModeUIOnly InputMode{};
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			PlayerController->SetInputMode(InputMode);
			UGameplayStatics::SetGamePaused(GetWorld(), true);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("EndGameWidget not found!"));
		}
	}
}

void APlayerPawn::CreateEndGameWidget()
{
	APlayerController* PlayerController = GetWorld()->GetFirstLocalPlayerFromController()->GetPlayerController(GetWorld());
	if (PlayerController)
	{
		if (HUDWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("HUDWidget collapsed"));
			HUDWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("HUDWidget not found!"));
		}

		if (TargetsCounterWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("TargetsCounterWidget collapsed"));
			TargetsCounterWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("TargetsCounterWidget not found!"));
		}

		UEndGameUI* EndGameWidget = CreateWidget<UEndGameUI>(PlayerController, EndGameWidgetClass);
		if (EndGameWidget)
		{
			EndGameWidget->AddToViewport();
			PlayerController->SetShowMouseCursor(true);
			FInputModeUIOnly InputMode{};
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			PlayerController->SetInputMode(InputMode);
			UGameplayStatics::SetGamePaused(GetWorld(), true);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("EndGameWidget not found!"));
		}
	}
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
	return BoostDuration;
}

int APlayerPawn::RetLaps()
{
	return FinishLineCrossed;
}


void APlayerPawn::RespawnFunction() {
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	playerCrashed = true;
	
}


// Collision

void APlayerPawn::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ATrackActor::StaticClass()) || OtherActor->IsA(ATunnelActor::StaticClass()) || OtherActor->IsA(AStartLineIndicatorColliderActor::StaticClass()) || OtherActor->IsA(ACrystalActor::StaticClass()) || OtherActor->IsA(ACrystalActorRed::StaticClass()) || OtherActor->IsA(ARegularBorderActor::StaticClass()) || OtherActor->IsA(ARoofBorderActorTwo::StaticClass()) /*&& playerCrashed == false*/)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			UE_LOG(LogTemp, Warning, TEXT("Ship hit the track."));
			/*GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("You crashed into the track!")));*/

			UGameplayStatics::PlaySound2D(World, DeathSound, 1.f, 1.f, 0.f, 0);

			Health--;
			RespawnFunction();
		}
	}

	else if (OtherActor->IsA(ACheckpointActor::StaticClass()))
	{
		ACheckpointActor* CheckpointPtr = Cast<ACheckpointActor>(OtherActor);

		CheckpointPtr->checkpointHidden = true;
		CheckpointsReached += 1;

		RespawnLocation = GetActorLocation();
		RespawnRotation = GetActorRotation();
		/*GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Yellow, FString::Printf(TEXT("Set Respawn location.")));
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Yellow, FString::Printf(TEXT("Set Respawn rotation.")));

		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Yellow, FString::Printf(TEXT("Player reached a checkpoint!")));*/
	}

	else if (OtherActor->IsA(ARoofBorderActorOne::StaticClass()) && RoofBorderTouched == false)
	{
		FloatingPawnMovementComp->MaxSpeed = 3000.0f;
		RoofBorderTouched = true;
		/*GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("Player is nearing dangerous altitudes!")));*/

		APlayerController* PlayerController = GetWorld()->GetFirstLocalPlayerFromController()->GetPlayerController(GetWorld());

		UWorld* World = GetWorld();
		if (World)
		{
			WarningWidget = CreateWidget<UBorderWarning_UI>(PlayerController, WarningWidgetClass);
			if (WarningWidget)
			{
				WarningWidget->AddToViewport();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("WarningWidget not found!"));
			}
		}
	}

}