// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Public/PlayerPawn.h"
#include "RacingGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RACINGGAME_API ARacingGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARacingGameGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Timer

	FTimerHandle StartTimer;

	UFUNCTION()
		void OnStartTimerComplete();

	bool gameHasStarted = false;

	// RaceTime

	float RaceTime;

	UFUNCTION(BlueprintCallable)
	float RetRaceTime();

private:


};


