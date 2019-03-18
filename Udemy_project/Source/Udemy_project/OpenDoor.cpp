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
	InitPressurePlate();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	(GetTotalMassOfActorsOnPlate() > this->TriggerMass) ? this->OnOpen.Broadcast() : this->OnClose.Broadcast();
}



float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	if (this->PressurePlate)
	{
		TArray<AActor*> ListOfOverLappingActors;
		this->PressurePlate->GetOverlappingActors(OUT ListOfOverLappingActors);
		for (const AActor* Actor : ListOfOverLappingActors)
		{
			TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}
	return TotalMass;
}


void UOpenDoor::InitPressurePlate()
{
	//Pressure plate is define in editor *set to EditAnywhere in header for front end definition
	if (!PressurePlate)
	{
		UE_LOG(LogTemp
			, Error
			, TEXT("PressurePlate is null for %s. Please Define a PressurePlate for OpenDoor component")
			, *GetOwner()->GetName());
	}
}

