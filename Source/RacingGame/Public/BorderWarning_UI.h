// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BorderWarning_UI.generated.h"

/**
 * 
 */
UCLASS()
class RACINGGAME_API UBorderWarning_UI : public UUserWidget
{
	GENERATED_BODY()
	
protected:


public:

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
