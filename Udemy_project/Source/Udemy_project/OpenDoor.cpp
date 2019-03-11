// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

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
	this->ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if the actor that opens is in the volume then open the door
	(this->PressurePlate->IsOverlappingActor(this->ActorThatOpens)) ? OpenDoor() : CloseDoor();

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

