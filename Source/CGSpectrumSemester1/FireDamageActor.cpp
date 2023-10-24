// Fill out your copyright notice in the Description page of Project Settings.


#include "FireDamageActor.h"
#include "DealDamageComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AFireDamageActor::AFireDamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DealDamageComponent = CreateDefaultSubobject<UDealDamageComponent>(TEXT("Deal Damage"));
	if (DealDamageComponent->GetTriggerCapsule())
	{
		SetRootComponent(DealDamageComponent->GetTriggerCapsule());
	}
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System"));
	ParticleSystemComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFireDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DealDamageComponent)
	{
		CurrentTime += DeltaTime;
		if (CurrentTime >= ToggleTime)
		{
			if (ParticleSystemComponent)
			{
				ParticleSystemComponent->ToggleActive();
			}
			DealDamageComponent->SetActive(!DealDamageComponent->IsActive());
			CurrentTime = 0.0f;
		}
	}
}

