// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "GameFramework/Actor.h"
#include "Public/DrawDebugHelpers.h"

#define OUT // blank definition for visual reference of 'OUT' variables 

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber for object: %s is online"), *(GetOwner()->GetName()))
	#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(1, 1.5, FColor::Green,text)
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// get Player View point this tick
	FVector OutLocation;
	FRotator OutRotation;
	GetOwner()->GetActorEyesViewPoint(OUT OutLocation, OUT OutRotation);
	print("\nPlayer View Point:\nLocation: " + OutLocation.ToString() 
			+ "\nRotation: " + OutRotation.ToString());
	//draw red trace
	FVector LineTRaceEnd = OutLocation + FVector(0.f, 0.f, 100.f);
	DrawDebugLine(
		GetWorld(),
		OutLocation,
		LineTRaceEnd,
		FColor::Cyan
	);
	// ray-cast to reach distance

	// see what we hit
}

