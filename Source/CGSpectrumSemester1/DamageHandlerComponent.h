// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HAL/CriticalSection.h"
#include "Misc/Optional.h"
#include "DamageHandlerComponent.generated.h"

class AAbstractionPlayerCharacter;
class UParticleSystem;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CGSPECTRUMSEMESTER1_API UDamageHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDamageHandlerComponent(const FObjectInitializer& ObjectInitializer);
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UParticleSystem* GetFireTemplate() { return FireTemplate; }

	AAbstractionPlayerCharacter* PlayerCharacter = nullptr;

	void TakeFireDamage(float BaseDamage, float DamageTotalTime, float TakeDamageInterval);

	struct FDamageInfo
	{
		float BaseDamage = 0.0f;
		float AccumulatedTime = 0.0f;
		float CurrentIntervalTime = 0.0f;
		float IntervalTime = 0.0f;
		float Lifetime = 0.0f;
	};

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Particles)
		class UParticleSystem* FireTemplate;

	TOptional<FDamageInfo> ActiveDamageInfo;

	/** Holds a critical section object. */
	FCriticalSection CriticalSection;

};
