// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget_UI.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Math/Color.h"

void UHUDWidget_UI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (PlayerPawnPtrs) {

		// Health

		float RemainingHealth = (float)PlayerPawnPtrs->RetHealth();
		float HealthBarPercent = float(RemainingHealth / (float)PlayerPawnPtrs->RetMaxHealth());

		if (RemainingHealth <= 5.f) {
			HealthBar->SetFillColorAndOpacity(FLinearColor(1.f, 0.f, 0.f));
		}

		HealthBar->SetPercent(HealthBarPercent);


		// Boost

		float RemainingBoost = (float)PlayerPawnPtrs->RetBoost();
		float BoostBarPercent = float(RemainingBoost / (float)PlayerPawnPtrs->RetMaxBoost());

		if (RemainingBoost >= 0.f && RemainingBoost <= 5.f) {
			BoostBar->SetFillColorAndOpacity(FLinearColor(1.f, 1.f, 0.f));
		}

		BoostBar->SetPercent(BoostBarPercent);


		// Laps

		Laps->SetText(FText::AsNumber(PlayerPawnPtrs->RetLaps()));


		// Time

		float RaceTime = (float)GameModeBasePtrs->RetRaceTime();
		Time->SetText(GetTimeTextFromFloat(RaceTime));


		// Targets

		/*TargetsShot->SetText(FText::AsNumber(TargetActorPtrs->RetTargetsShot()));*/

	}

}

FText UHUDWidget_UI::GetTimeTextFromFloat(float RaceTime)
{
	int32 Minutes = FMath::FloorToInt(RaceTime / 60);
	int32 Seconds = FMath::FloorToInt(FMath::Fmod(RaceTime, 60.f));
	int32 CentiSeconds = FMath::FloorToInt((FMath::Fmod(RaceTime, 60.f) - Seconds) * 100);
	FString	TimeString{ FString::Printf(TEXT("%02d:%02d:%02d"), Minutes, Seconds, CentiSeconds) };

	return FText::FromString(TimeString);
}
