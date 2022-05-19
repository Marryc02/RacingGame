// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TargetActor.h"
#include "TargetsShotCounter_UI.generated.h"

/**
 * 
 */
UCLASS()
class RACINGGAME_API UTargetsShotCounter_UI : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/*class ATargetActor* TargetActorPtrs = Cast<ATargetActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));*/
	class APlayerPawn* PlayerPawnPtr{ nullptr };
	/*Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));*/

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
		class UTextBlock* TargetsShotCounter;

public:

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
