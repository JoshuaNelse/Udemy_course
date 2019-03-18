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
	InitializePlayerToTeleport();
	InitializeRemoteLocation();
	InitializeRemoteTeleporter();
	InitializeLocalLocation();
}



// Called every frame
void UTeleporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TeleportPlayerWhenCollidingWithVolume();
}


void UTeleporter::TeleportPlayerWhenCollidingWithVolume()
{
	if (!LocalVolume || !PlayerToTeleport || !RemoteTeleporter) {
		return; //guarding null pointers
	}

	if (LocalVolume->IsOverlappingActor(PlayerToTeleport))
	{
		if (!bCoolingDown)
		{
			PlayerToTeleport->SetActorLocation(RemoteLocation);
			RemoteTeleporter->FindComponentByClass<UTeleporter>()->SetbCoolingDown(true);
		}
	}
	else
	{
		this->bCoolingDown = false;
	}
}


void UTeleporter::SetbCoolingDown(bool Boolean)
{
	this->bCoolingDown = Boolean;
}


void UTeleporter::InitializeRemoteLocation()
{
	if (RemoteTeleporter)
	{
		auto RemoteVolume = RemoteTeleporter->FindComponentByClass<UTeleporter>();
		if (RemoteVolume->LocalVolume) 
		{
			this->RemoteLocation = RemoteVolume->LocalVolume->GetActorLocation();
		}
		else
		{
			UE_LOG(LogTemp
				, Error
				, TEXT("Local teleporter %s cannot find remote volume for %s. Please assign a local volume for %s")
				, *GetOwner()->GetName()
				, *this->RemoteTeleporter->GetName()
				, *this->RemoteTeleporter->GetName());
		}
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

void UTeleporter::InitializePlayerToTeleport()
{
	this->PlayerToTeleport = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerToTeleport) {
		UE_LOG(LogTemp, Error, TEXT("Failed to init PlayerToTeleport for %s"), *GetOwner()->GetName());
	}
}



