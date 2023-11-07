// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoor.h"
#include "DoorInteractionComponent.h"
#include "Components/CapsuleComponent.h"
#include "AbstractionPlayerCharacter.h"

AInteractableDoor::AInteractableDoor()
{
	DoorInteractionComp = CreateDefaultSubobject<UDoorInteractionComponent>(TEXT("Door Interaction Component"));
	if (DoorInteractionComp->GetTriggerCapsule())
	{
		DoorInteractionComp->GetTriggerCapsule()->SetupAttachment(RootComponent);
	}
}

void AInteractableDoor::BeginPlay()
{
	Super::BeginPlay();
	DoorInteractionComp->InteractionSuccess.AddDynamic(this, &AInteractableDoor::OnInteractionSuccess);
}

void AInteractableDoor::OnInteractionSuccess()
{
	OnDoorOpen.Broadcast();
}