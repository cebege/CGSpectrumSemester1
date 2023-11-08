// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveComp.h"
#include "ObjectiveWorldSubsystem.h"

// Sets default values
UObjectiveComp::UObjectiveComp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;
	State = EObjectiveState::OS_Inactive;

}

void UObjectiveComp::SetState(EObjectiveState NewState)
{
	if (NewState != State)
	{
		State = NewState;
		StateChangedEvent.Broadcast(this, State);
	}
}

// Called when the game starts or when spawned
void UObjectiveComp::InitializeComponent()
{
	Super::InitializeComponent();
	UE_LOG(LogTemp, Warning, TEXT("UObjectiveComp::InitializeComponent called for %s"), *GetName());

	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->AddObjective(this);
		UE_LOG(LogTemp, Warning, TEXT("Objective added to World Subsystem."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ObjectiveWorldSubsystem not found!"));
	}
}

void UObjectiveComp::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->RemoveObjective(this);
	}
	Super::EndPlay(EndPlayReason);
}

