// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Public/DrawDebugHelpers.h"

#define OUT // blank definition for visual reference of 'OUT' variables 

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	InitializePhysicsHandle();
	InitializeInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
	}
}


void UGrabber::InitializePhysicsHandle()
{
	this->PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Physics handle for %s is null or undefined"), *(GetOwner()->GetName()));
	}
}


void UGrabber::InitializeInputComponent()
{
	this->InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (this->InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input Component initialized for %s"), *(GetOwner()->GetName()));
		this->InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		this->InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input Component for %s is Null or undefined."), *(GetOwner()->GetName()));
	}
}


void UGrabber::Grab()
{
	FHitResult CollisionWithinReach = this->GetFirstPhysicsBodyinReach();
	UPrimitiveComponent* ComponentToGrab = CollisionWithinReach.GetComponent();
	//AActor* ActorHit = ObjectInReach.GetActor();

	if (CollisionWithinReach.GetActor() != nullptr) // verify something can be grabbed
	{
		this->PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation()
		);
	}
}


void UGrabber::Release()
{
	this->PhysicsHandle->ReleaseComponent();
}


FVector UGrabber::GetLineTraceEnd()
{
	//This refreshes the OUT variables to make the TraceEnd Value accurate to last frame.
	GetOwner()->GetActorEyesViewPoint(OUT this->ObjectLocation, OUT this->ObjectRotation);
	return (this->ObjectLocation + (this->ObjectRotation.Vector() * this->Reach));
}


FHitResult UGrabber::GetFirstPhysicsBodyinReach()
{
	FCollisionQueryParams TraceParms(FName(TEXT("")), false, GetOwner());
	FHitResult OutHit;

	GetWorld()->LineTraceSingleByObjectType(
		OUT OutHit, 
		this->ObjectLocation, 
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParms
	);

	return OutHit;
}