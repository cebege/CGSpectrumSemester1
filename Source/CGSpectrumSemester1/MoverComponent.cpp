// Fill out your copyright notice in the Description page of Project Settings.


#include "MoverComponent.h"

// Sets default values for this component's properties
UMoverComponent::UMoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetOwner()->GetActorLocation();
}

// Called every frame
void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);

	// ...
}

void UMoverComponent::MovePlatform(float DeltaTime)
{
	if (ShouldPlatformMove()) // at the turning point.
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		GetOwner()->SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else // the continuous movement between turning points.
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		GetOwner()->SetActorLocation(CurrentLocation);
	}
}

void UMoverComponent::RotatePlatform(float DeltaTime)
{
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation = CurrentRotation + RotationVelocity * DeltaTime;
	GetOwner()->SetActorRotation(CurrentRotation);
}

bool UMoverComponent::ShouldPlatformMove() const
{
	return GetDistanceMoved() > MoveDistance;
}

float UMoverComponent::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetOwner()->GetActorLocation());
}