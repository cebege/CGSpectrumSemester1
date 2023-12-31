//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "ObjectiveComponent.h"
//#include "ObjectiveWorldSubsystem.h"
//
//// Sets default values
//AObjectiveComponent::AObjectiveComponent()
//{
// 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = false;
//	State = EObjectiveState::OS_Inactive;
//
//}
//
//void AObjectiveComponent::SetState(EObjectiveState NewState)
//{
//	if (NewState != State)
//	{
//		State = NewState;
//		StateChangedEvent.Broadcast(this, State);
//	}
//}
//
//// Called when the game starts or when spawned
//void AObjectiveComponent::BeginPlay()
//{
//	Super::BeginPlay();
//
//	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
//	if (ObjectiveWorldSubsystem)
//	{
//		ObjectiveWorldSubsystem->AddObjective(this);
//	}
//	
//}
//
//void AObjectiveComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
//{
//	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
//	if (ObjectiveWorldSubsystem)
//	{
//		ObjectiveWorldSubsystem->RemoveObjective(this);
//	}
//	Super::EndPlay(EndPlayReason);
//}
