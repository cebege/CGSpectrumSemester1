// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "CGSpectrumSemester1GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CGSPECTRUMSEMESTER1_API ACGSpectrumSemester1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void StartPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf< class UUserWidget> ObjectiveWidgetClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf< class UUserWidget> ObjectiveCompleteWidgetClass;
};
