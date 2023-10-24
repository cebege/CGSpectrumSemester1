// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoverComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CGSPECTRUMSEMESTER1_API UMoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoverComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MovePlatform(float DeltaTime);
	void RotatePlatform(float DeltaTime);
	bool ShouldPlatformMove() const;
	float GetDistanceMoved() const;

private:

	UPROPERTY(EditAnywhere, Category = "Moving Platform")
		FVector PlatformVelocity;

	UPROPERTY(EditAnywhere, Category = "Moving Platform")
	float MoveDistance = 100;

	UPROPERTY(EditAnywhere, Category = "Rotating Platform")
		FRotator RotationVelocity;

	FVector StartLocation;


		
};