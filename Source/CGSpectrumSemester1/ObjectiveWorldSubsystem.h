// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectiveComp.h"
#include "ObjectiveWorldSubsystem.generated.h"

UCLASS()
class CGSPECTRUMSEMESTER1_API UObjectiveWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void CreateObjectiveWidget(TSubclassOf<class UUserWidget> ObjectiveWidgetClass);
	void DisplayObjectiveWidget();

	void OnObjectiveCompleted();

	UFUNCTION(BlueprintCallable)
		FString GetCurrentObjectiveDescription();

	UFUNCTION(BlueprintCallable)
		void AddObjective(UObjectiveComp* ObjectiveComponent);

	UFUNCTION(BlueprintCallable)
		void RemoveObjective(UObjectiveComp* ObjectiveComponent);

	void OnObjectiveStateChanged(UObjectiveComp* ObjectiveComponent, EObjectiveState ObjectiveState);

private:
	UUserWidget* ObjectiveWidget = nullptr;

	TArray<UObjectiveComp*> Objectives;

	
};
