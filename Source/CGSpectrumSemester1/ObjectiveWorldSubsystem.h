// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectiveComp.h"
#include "ObjectiveHud.h"
#include "ObjectiveWorldSubsystem.generated.h"

UCLASS()
class CGSPECTRUMSEMESTER1_API UObjectiveWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void CreateObjectiveWidgets();
	void DisplayObjectiveWidget();

	void OnObjectiveCompleted();

	void OnMapStart();

	UFUNCTION(BlueprintCallable)
		FString GetCurrentObjectiveDescription();

	UFUNCTION(BlueprintCallable)
		void AddObjective(UObjectiveComp* ObjectiveComponent);

	UFUNCTION(BlueprintCallable)
		void RemoveObjective(UObjectiveComp* ObjectiveComponent);

	void OnObjectiveStateChanged(UObjectiveComp* ObjectiveComponent, EObjectiveState ObjectiveState);

	void virtual Deinitialize() override;

	uint32 GetCompletedObjectiveCount();

	void DisplayObjectivesCompleteWidget();

	void RemoveObjectivesCompleteWidget();

	void RemoveObjectiveWidget();

private:
	UObjectiveHud* ObjectiveWidget = nullptr;

	UUserWidget* ObjectivesCompleteWidget = nullptr;

protected:

	TArray<UObjectiveComp*> Objectives;

	
};
