// Fill out your copyright notice in the Description page of Project Settings.

#include "SecurityOverrideButton.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
USecurityOverrideButton::USecurityOverrideButton()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USecurityOverrideButton::BeginPlay()
{
	Super::BeginPlay();

	this->CurrentLeftDoorRotation = this->LeftDoor->GetActorRotation();
	this->CurrentRightDoorRotation = this->RightDoor->GetActorRotation();
	this->MaxLeftDoorRotation.Yaw = CurrentLeftDoorRotation.Yaw + 110.f;
	// ...
	this->PlayerPressingButton = GetWorld()->GetFirstPlayerController()->GetPawn();
	if(PlayerPressingButton)
	this->PlayerInputComponent = PlayerPressingButton->FindComponentByClass<UInputComponent>();
	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAction("Push_Button", IE_Pressed, this, &USecurityOverrideButton::PushButton);
	}
}


// Called every frame
void USecurityOverrideButton::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckIfPlayerIsInRange();
	OpenDoubleDoorsHandler();
}

void USecurityOverrideButton::CheckIfPlayerIsInRange()
{
	if (!bButtonsBeenPushed)
	{
		bCanPushButton = (ButtonPressRangeVolume->IsOverlappingActor(PlayerPressingButton)) ? true : false;
	}
}

void USecurityOverrideButton::OpenDoubleDoorsHandler()
{
	if (bDoorsOpening)
	{
		OpenLeftDoor();
		OpenRightDoor();
		StopDoorsWhenFullyOpened();
	}
}


void USecurityOverrideButton::OpenLeftDoor()
{
	CurrentLeftDoorRotation.Yaw += OpenSpeed;
	LeftDoor->SetActorRotation(CurrentLeftDoorRotation);
}


void USecurityOverrideButton::OpenRightDoor()
{
	CurrentRightDoorRotation.Yaw -= OpenSpeed;
	RightDoor->SetActorRotation(CurrentRightDoorRotation);
}


void USecurityOverrideButton::StopDoorsWhenFullyOpened()
{
	if (CurrentLeftDoorRotation.Yaw >= MaxLeftDoorRotation.Yaw)
	{
		bDoorsOpening = false;
	}
}


void USecurityOverrideButton::PushButton()
{
	if (bCanPushButton)
	{
		SetButtonColorGreen();
		UpdateButtonLocation();
		SetStatesForDoorsOpening();
	}
}

void USecurityOverrideButton::SetStatesForDoorsOpening()
{
	bDoorsOpening = true;
	bButtonsBeenPushed = true;
	bCanPushButton = false;
}

void USecurityOverrideButton::SetButtonColorGreen()
{
	if (GreenMaterial != nullptr)
	{
		GetOwner()->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0, GreenMaterial);
	}
}

void USecurityOverrideButton::UpdateButtonLocation()
{
	FVector Offset = FVector(0, -1, 0);
	GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + Offset);
}
