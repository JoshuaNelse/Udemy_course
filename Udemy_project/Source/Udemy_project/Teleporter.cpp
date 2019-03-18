// Fill out your copyright notice in the Description page of Project Settings.

#include "Teleporter.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UTeleporter::UTeleporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTeleporter::BeginPlay()
{
	Super::BeginPlay();
	this->PlayerToTeleport = GetWorld()->GetFirstPlayerController()->GetPawn();
	InitializeRemoteLocation();
	InitializeRemoteTeleporter();
	InitializeLocalLocation();
}


// Called every frame
void UTeleporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!LocalVolume || !PlayerToTeleport || !RemoteTeleporter) return; // guarding null pointers

	if (LocalVolume->IsOverlappingActor(PlayerToTeleport))
	{
		if (!IsCoolingDown)
		{
			PlayerToTeleport->SetActorLocation(RemoteLocation);
			RemoteTeleporter->FindComponentByClass<UTeleporter>()->IsCoolingDown = true;
		}
	} 
	else
	{
		this->IsCoolingDown = false;
	}

}


void UTeleporter::InitializeRemoteLocation()
{
	if (this->RemoteVolume) {
		this->RemoteLocation = this->RemoteVolume->GetActorLocation();
	}
	else {
		UE_LOG(LogTemp
			, Error
			, TEXT("Teleporter %s has no Remote Volume defined. please add a Remote Volume")
			, *GetOwner()->GetName());
	}
}


void UTeleporter::InitializeLocalLocation()
{
	if (this->LocalVolume)
	{
		this->LocalLocation = this->LocalVolume->GetActorLocation();
	}
	else {
		UE_LOG(LogTemp
			, Error
			, TEXT("Teleporter %s has no Local Volume defined. please add a Local Volume")
			, *GetOwner()->GetName());
	}
}


void UTeleporter::InitializeRemoteTeleporter()
{
	if (!RemoteTeleporter) {
		UE_LOG(LogTemp
			, Error
			, TEXT("Teleporter %s has no Remote Teleporter defined. please add a Remote Teleporter")
			, *GetOwner()->GetName());
	}
}



