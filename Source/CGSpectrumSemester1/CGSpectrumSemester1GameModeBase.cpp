// Copyright Epic Games, Inc. All Rights Reserved.


#include "CGSpectrumSemester1GameModeBase.h"
#include "ObjectiveWorldSubsystem.h"


void ACGSpectrumSemester1GameModeBase::StartPlay()
{
	Super::StartPlay();

	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->CreateObjectiveWidget(ObjectiveWidgetClass);
		ObjectiveWorldSubsystem->DisplayObjectiveWidget();
	}

}


