// Copyright Epic Games, Inc. All Rights Reserved.


#include "RacingGameGameModeBase.h"
#include "Public/EndGameUI.h"
#include "PlayerPawn.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

ARacingGameGameModeBase::ARacingGameGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ARacingGameGameModeBase::BeginPlay()
{
	//Timer BeginPlay

	GetWorld()->GetTimerManager().SetTimer(StartTimer, this, &ARacingGameGameModeBase::OnStartTimerComplete, 3.f, false);

}

void ARacingGameGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Timer-related tick

	if (gameHasStarted)
	{
		RaceTime += DeltaTime;
	}

	FinalRaceTime = RaceTime; 


}

//Timer-related

void ARacingGameGameModeBase::OnStartTimerComplete()
{
	APlayerController* PlayerController = GetWorld()->GetFirstLocalPlayerFromController()->GetPlayerController(GetWorld());
	FInputModeGameAndUI InputMode{};
	PlayerController->SetInputMode(InputMode);
	gameHasStarted = true;
}

float ARacingGameGameModeBase::RetRaceTime()
{
	return RaceTime;
}

float ARacingGameGameModeBase::RetFinalRaceTime()
{
	return FinalRaceTime;
}

//void ARacingGameGameModeBase::CreateEndGameWidget()
//{
//	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
//	if (PlayerController)
//	{
//		UEndGameUI* EndGameWidget = CreateWidget<UEndGameUI>(PlayerController, EndGameWidgetClass.Get());
//		PlayerController->SetShowMouseCursor(true);
//		FInputModeUIOnly InputMode{};
//		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
//		PlayerController->SetInputMode(InputMode);
//	}
//}
