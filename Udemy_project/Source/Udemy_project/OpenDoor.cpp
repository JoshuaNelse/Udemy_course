// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#define OUT
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	this->Owner = GetOwner();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if the actor that opens is in the volume then open the door
		(GetTotalMassOfActorsOnPlate() > 20.f) ? OpenDoor() : CloseDoor();
}

void UOpenDoor::CloseDoor()
{
	if (IsDoorTimerExhausted())
	{
		this->Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
	}
}

bool UOpenDoor::IsDoorTimerExhausted()
{
	return (GetWorld()->GetTimeSeconds() - this->DoorOpenTimestamp) > this->StayOpenTime;
}

void UOpenDoor::OpenDoor()
{
	this->Owner->SetActorRotation(FRotator(0.f, 75.f, 0.f));
	SetLastDoorOpenTimestamp();
}

void UOpenDoor::SetLastDoorOpenTimestamp()
{
	this->DoorOpenTimestamp = GetWorld()->GetTimeSeconds();
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	TArray<AActor*> ListOfOverLappingActors;
	this->PressurePlate->GetOverlappingActors(OUT ListOfOverLappingActors);
	for (AActor* Actor : ListOfOverLappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("Mass on Plate: %s - %f")
			, *Actor->GetName()
			, TotalMass);
	}
	return TotalMass;
}

