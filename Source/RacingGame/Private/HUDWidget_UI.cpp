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


		// Ammo

		AmmoNO->SetText(FText::AsNumber(PlayerPawnPtrs->RetAmmo()));
	}

}