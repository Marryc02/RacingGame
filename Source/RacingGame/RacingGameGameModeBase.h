// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
//#include "Public/PlayerPawn.h"
#include "RacingGameClasses.h"
#include "Kismet/GameplayStatics.h"
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


	/*class APlayerPawn* PlayerPawnPtrs = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));*/

	// Timer

	FTimerHandle StartTimer;

	UFUNCTION()
		void OnStartTimerComplete();

	bool gameHasStarted = false;

	// RaceTime

	float RaceTime;
	float FinalRaceTime = 0.0f;

	UFUNCTION(BlueprintCallable)
	float RetRaceTime();

	UFUNCTION(BlueprintCallable)
	float RetFinalRaceTime();

	/*UFUNCTION(BlueprintCallable)
		void CreateEndGameWidget();*/


	// Widget

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> EndGameWidgetClass;*/

private:


};


