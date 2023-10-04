// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#include "DrawDebugHelpers.h"

constexpr float FLT_METERS(float meters) { return meters * 100.f; }

static TAutoConsoleVariable<bool>CVarToggleDebugDoor(
	TEXT("CGSpectrumSemester1.DoorInteractionComponent.Debug"),
	false,
	TEXT("Toggle DoorInteractionComponent debug display"),
	ECVF_Default);

// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	DoorState = EDoorState::DS_Closed;

	CVarToggleDebugDoor.AsVariable()->SetOnChangedCallback(FConsoleVariableDelegate::CreateStatic(&UDoorInteractionComponent::OnDebugToggled));

	// ...
}


// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	StartRotation = GetOwner()->GetActorRotation();
	FinalRotation = StartRotation + DesiredRotation;

	// ...

}

// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentRotationTime < TimeToRotate)
	{
		if (TriggerBox && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
		{
			APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			if (Pawn && TriggerBox->IsOverlappingActor(Pawn))
			{
				CurrentRotationTime += DeltaTime;
				const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
				const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
				FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
				GetOwner()->SetActorRotation(CurrentRotation);
				DoorState = EDoorState::DS_Open;
			}
		}
	}

	DebugDraw();
}

void UDoorInteractionComponent::OnDebugToggled(IConsoleVariable* Var)
{
	UE_LOG(LogTemp, Warning, TEXT("OnDebugToggled"));
}

void UDoorInteractionComponent::DebugDraw()
{
	if (CVarToggleDebugDoor->GetBool())
	{
		FVector Offset(FLT_METERS(-0.75f), 0.0f, FLT_METERS(1.5f));
		FVector StartLocation = GetOwner()->GetActorLocation() + Offset;
		FString UEnumAsString = TEXT("Door State: ") + UEnum::GetDisplayValueAsText(DoorState).ToString();
		DrawDebugString(GetWorld(), Offset, UEnumAsString, GetOwner(), FColor::Blue, 0.0f);
	}
}