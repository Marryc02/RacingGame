// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetsShotCounter_UI.h"
#include "Components/TextBlock.h"

void UTargetsShotCounter_UI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (PlayerPawnPtr == nullptr)
	{
		PlayerPawnPtr = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	}
	if (PlayerPawnPtr != nullptr)
	{
		int TargetsShot = (int)PlayerPawnPtr->TargetsShotCount;
		TargetsShotCounter->SetText(FText::AsNumber(TargetsShot));
	}

}