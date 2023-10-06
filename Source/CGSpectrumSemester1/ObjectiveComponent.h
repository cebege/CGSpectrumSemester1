// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
//#include "ObjectiveComponent.generated.h"
//
//UENUM()
//enum class EObjectiveState
//{
//	OS_Inactive = 0	UMETA(DisplayName = "Inactive"),
//	OS_Active = 1	UMETA(DisplayName = "Active"),
//	OS_Completed = 2 UMETA(DisplayName = "Completed"),
//};
//
//UCLASS()
//class CGSPECTRUMSEMESTER1_API AObjectiveComponent : public AActor
//{
//	GENERATED_BODY()
//	
//public:	
//	// Sets default values for this actor's properties
//	AObjectiveComponent();
//
//	UFUNCTION(BlueprintCallable)
//		const FString& GetDescription() const { return Description; }
//
//	DECLARE_EVENT_TwoParams(FObjectiveComponent, FStateChanged, UObjectiveComponent*, EObjectiveState)
//	FStateChanged& OnStateChanged() { return StateChangedEvent; }
//
//	UFUNCTION(BlueprintCallable)
//		EObjectiveState GetState() const { return State; }
//
//	void SetState(EObjectiveState NewState);
//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//	UPROPERTY(EditAnywhere)
//		FString Description;
//
//	UPROPERTY(EditAnywhere)
//		EObjectiveState State;
//
//	FStateChanged StateChangedEvent;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//};
