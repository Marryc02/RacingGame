// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerPawn.h"
#include "RacingGameClasses.h"
#include "Kismet/GameplayStatics.h"
#include "../RacingGameGameModeBase.h"
#include "HUDWidget_UI.generated.h"

/**
 * 
 */
UCLASS()
class RACINGGAME_API UHUDWidget_UI : public UUserWidget
{
	GENERATED_BODY()
	
public:

	APlayerPawn* PlayerPawnPtrs = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	class UProgressBar* BoostBar;

public:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
