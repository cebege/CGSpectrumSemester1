// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject< UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsuleComponent;

	StaticMeshComponent = CreateDefaultSubobject< UStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->SetupAttachment(CapsuleComponent);

	SpringArmComponent = CreateDefaultSubobject< USpringArmComponent>(TEXT("Spring Component"));
	SpringArmComponent->SetupAttachment(StaticMeshComponent);

	CameraComponent = CreateDefaultSubobject< UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerPawn::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerPawn::Turn);
}

void APlayerPawn::Move(float input)
{
	FVector DeltaLocation;
	DeltaLocation.X = input * MovementSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation);
	UE_LOG(LogTemp, Warning, TEXT("Move Input: %f"), input);
}

void APlayerPawn::Turn(float input)
{
	FRotator DeltaRotation;
	DeltaRotation.Yaw = input * TurnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation);
	UE_LOG(LogTemp, Warning, TEXT("Turn Input: %f"), input);
}



