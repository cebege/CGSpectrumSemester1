// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorInteractionComponent.generated.h"

class ATriggerBox;
class IConsoleVariable;

UENUM()
enum class EDoorState
{
	DS_Closed = 0	UMETA(DisplayName = "Closed"),
	DS_Opening = 1		UMETA(DisplayName = "Opening"),
	DS_Open = 2		UMETA(DisplayName = "Open"),
	DS_Locked = 3	UMETA(DisplayName = "Locked"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CGSPECTRUMSEMESTER1_API UDoorInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	DECLARE_EVENT(FDoorInteractionComponent, FOpened)
	FOpened& onOpened() { return OpenedEvent; }

	FOpened OpenedEvent;
	
	static void OnDebugToggled(IConsoleVariable* Var);
	void DebugDraw();
	void OnDoorOpen();

protected:

	UPROPERTY(EditAnywhere, Category = "Moving Door Component")
		FRotator DesiredRotation = FRotator::ZeroRotator;

	FRotator StartRotation = FRotator::ZeroRotator;
	FRotator FinalRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, Category = "Moving Door Component")
		float TimeToRotate = 4.0f;

		float CurrentRotationTime = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Moving Door Component")
	ATriggerBox* TriggerBox;

	UPROPERTY(EditAnywhere, Category = "Moving Door Component")
	FRuntimeFloatCurve OpenCurve;

	UPROPERTY(BlueprintReadOnly)
	EDoorState DoorState;



		
};
