// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Components/InputComponent.h"
#include "SecurityOverrideButton.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEMY_PROJECT_API USecurityOverrideButton : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USecurityOverrideButton();

private:
	FRotator CurrentLeftDoorRotation;
	FRotator CurrentRightDoorRotation;
	FRotator MaxLeftDoorRotation;

	bool bCanPushButton = false;
	bool bDoorsOpening = false;
	bool bButtonsBeenPushed = false; //this button can only be pushed once.

	UPROPERTY(EditAnywhere)
	float OpenSpeed = .3;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void PushButton();
	void SetStatesForDoorsOpening();
	void SetButtonColorGreen();
	void UpdateButtonLocation();
	void OpenDoubleDoorsHandler();
	void StopDoorsWhenFullyOpened();
	void OpenRightDoor();
	void OpenLeftDoor();
	void CheckIfPlayerIsInRange();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//double doors require special handling
	UPROPERTY(EditAnywhere)
	AActor*	LeftDoor= nullptr;
	UPROPERTY(EditAnywhere)
	AActor*	RightDoor = nullptr;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* ButtonPressRangeVolume = nullptr;

	AActor* PlayerPressingButton = nullptr;
	UInputComponent* PlayerInputComponent = nullptr;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* GreenMaterial;
};
