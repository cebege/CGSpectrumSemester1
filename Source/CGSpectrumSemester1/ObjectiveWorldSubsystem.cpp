// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveWorldSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveComp.h"

void UObjectiveWorldSubsystem::CreateObjectiveWidget(TSubclassOf<class UUserWidget> ObjectiveWidgetClass)
{
	if (ObjectiveWidget == nullptr)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		ObjectiveWidget = CreateWidget<UUserWidget>(PlayerController, ObjectiveWidgetClass);
	}
}

void UObjectiveWorldSubsystem::DisplayObjectiveWidget()
{
	ensureMsgf(ObjectiveWidget, TEXT("UObjectiveWorldSubsystem::DisplayObjectiveWidget ObjectiveWidget is nullptr"));
	ObjectiveWidget->AddToViewport();

}

void UObjectiveWorldSubsystem::OnObjectiveCompleted()
{
	DisplayObjectiveWidget();
}

FString UObjectiveWorldSubsystem::GetCurrentObjectiveDescription()
{
	if (!Objectives.IsValidIndex(0) || Objectives[0]->GetState() == EObjectiveState::OS_Inactive)
	{
		return TEXT("N/A");
	}

	FString RetObjective = Objectives[0]->GetDescription();
	if (Objectives[0]->GetState() == EObjectiveState::OS_Completed)
	{
		RetObjective += TEXT("Completed!");
	}
	return RetObjective;
}

void UObjectiveWorldSubsystem::AddObjective(UObjectiveComp* ObjectiveComponent)
{
	check(ObjectiveComponent);

	size_t PrevSize = Objectives.Num();
	Objectives.AddUnique(ObjectiveComponent);
	if (Objectives.Num() > PrevSize)
	{
		ObjectiveComponent->OnStateChanged().AddUObject(this, &UObjectiveWorldSubsystem::OnObjectiveStateChanged);
	}
}

void UObjectiveWorldSubsystem::RemoveObjective(UObjectiveComp* ObjectiveComponent)
{
	Objectives.Remove(ObjectiveComponent);
}

void UObjectiveWorldSubsystem::OnObjectiveStateChanged(UObjectiveComp* ObjectiveComponent, EObjectiveState ObjectiveState)
{
	DisplayObjectiveWidget();
}