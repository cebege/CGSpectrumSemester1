// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"
#include "Engine/TriggerBox.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerController.h"
#include "ObjectiveWorldSubsystem.h"

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

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Render Component"));
	TextRenderComponent->SetupAttachment(TriggerCapsule);

	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerComponent"));
	TriggerComponent->SetBoxExtent(FVector(100, 100, 100)); 
	TriggerComponent->SetCollisionProfileName(TEXT("Trigger"));

	CVarToggleDebugDoor.AsVariable()->SetOnChangedCallback(FConsoleVariableDelegate::CreateStatic(&UDoorInteractionComponent::OnDebugToggled));
	// ...
}

void UDoorInteractionComponent::InteractionStart()
{
	Super::InteractionStart();
	if (InteractingActor)
	{
		OpenDoor();
	}
}

// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	StartRotation = GetOwner()->GetActorRotation();
	FinalRotation = StartRotation + DesiredRotation;
	CurrentRotationTime = 0.0f;

	TextRenderComponent = GetOwner()->FindComponentByClass<UTextRenderComponent>();
	//AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (AudioComponent)
	{
		AudioComponent->bAutoActivate = false; // Prevents the component from playing on BeginPlay
		AudioComponent->Deactivate();
	}
}

void UDoorInteractionComponent::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep)
{
	UE_LOG(LogTemp, Warning, TEXT("UDoorInteractionComponent::OnOverlapBegin"));
	// we already have somebody interacting, currently we don't support multiple interactions
	if (InteractingActor || !bActive)
	{
		return;
	}

	// for now we will get that component and set visible

	if (OtherActor->ActorHasTag("Player"))
	{
		InteractingActor = OtherActor;
		if (TextRenderComponent)
		{
			TextRenderComponent->SetText(InteractionPrompt);
			TextRenderComponent->SetVisibility(true);
		}
	}
}

void UDoorInteractionComponent::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("UDoorInteractionComponent::OnOverlapEnd"));
	if (OtherActor == InteractingActor)
	{
		InteractingActor = nullptr;
		if (TextRenderComponent)
		{
			TextRenderComponent->SetVisibility(false);
		}
	}
}

void UDoorInteractionComponent::OpenDoor()
{
	UE_LOG(LogTemp, Warning, TEXT("OpenDoor() called"));

	if (IsOpen() || DoorState == EDoorState::DS_Opening)
	{
		return;
	}

	if (AudioComponent)
	{
		AudioComponent->Play();
	}

	DoorState = EDoorState::DS_Opening;
	CurrentRotationTime = 0.0f;
}

// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (DoorState == EDoorState::DS_Closed)
	{
		if (TriggerComponent && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
		{
			APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			if (Pawn && TriggerComponent->IsOverlappingActor(Pawn))
			{
				if (AudioComponent)
				{
					AudioComponent->Play();
				}
				DoorState = EDoorState::DS_Opening;
				CurrentRotationTime = 0.0f;
			}
		}
	}
	else if (DoorState == EDoorState::DS_Opening)
	{
		CurrentRotationTime += DeltaTime;
		const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
		const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
		FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
		GetOwner()->SetActorRotation(CurrentRotation);
		if (TimeRatio >= 1.0f)
		{
			OnDoorOpen();
		}
	}
	DebugDraw();
}

void UDoorInteractionComponent::OnDoorOpen()
{
	DoorState = EDoorState::DS_Open;

	UObjectiveComp* ObjectiveComponent = GetOwner()->FindComponentByClass<UObjectiveComp>();
	if (ObjectiveComponent)
	{
		ObjectiveComponent->SetState(EObjectiveState::OS_Completed);
	}
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("DoorOpened"));
	InteractionSuccess.Broadcast();
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