// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameUI.h"
#include "Components/TextBlock.h"
#include "Math/Color.h"

void UEndGameUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (PlayerPawnPtrs->RetLaps() == 3)
	{
		float FinalRaceTime = (float)GameModeBasePtrs->RaceTime;
		FinalTime->SetText(GetFinalTimeTextFromFloat(FinalRaceTime));
	}

}

FText UEndGameUI::GetFinalTimeTextFromFloat(float FinalRaceTime)
{
	int32 Minutes = FMath::FloorToInt(FinalRaceTime / 60);
	int32 Seconds = FMath::FloorToInt(FMath::Fmod(FinalRaceTime, 60.f));
	int32 CentiSeconds = FMath::FloorToInt((FMath::Fmod(FinalRaceTime, 60.f) - Seconds) * 100);
	FString	TimeString{ FString::Printf(TEXT("%02d:%02d:%02d"), Minutes, Seconds, CentiSeconds) };

	return FText::FromString(TimeString);
}
