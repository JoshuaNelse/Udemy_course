// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Teleporter.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEMY_PROJECT_API UTeleporter : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTeleporter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void InitializeRemoteTeleporter();
	void InitializeLocalLocation();
	void InitializeRemoteLocation();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* RemoteVolume = nullptr;
	AActor* PlayerToTeleport = nullptr;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* LocalVolume = nullptr;
	UPROPERTY(EditAnywhere)
	AActor* RemoteTeleporter;

private:
	FVector RemoteLocation;
	FVector LocalLocation;
	bool IsCoolingDown = false;
};
