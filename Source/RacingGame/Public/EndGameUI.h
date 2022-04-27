// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../RacingGameGameModeBase.h"
#include "EndGameUI.generated.h"

/**
 * 
 */
UCLASS()
class RACINGGAME_API UEndGameUI : public UUserWidget
{
	GENERATED_BODY()
	
public:

	// Cast

	ARacingGameGameModeBase* GameModeBasePtrs = Cast<ARacingGameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));


	// Functions

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	FText GetFinalTimeTextFromFloat(float FinalRaceTime);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
		class UTextBlock* FinalTime;

};