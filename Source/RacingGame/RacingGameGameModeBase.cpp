// Copyright Epic Games, Inc. All Rights Reserved.


#include "RacingGameGameModeBase.h"

ARacingGameGameModeBase::ARacingGameGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ARacingGameGameModeBase::BeginPlay()
{
	GetWorld()->GetTimerManager().SetTimer(StartTimer, this, &ARacingGameGameModeBase::OnStartTimerComplete, 3.f, false);
}

void ARacingGameGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (gameHasStarted)
	{
		RaceTime += DeltaTime;
	}

}

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
