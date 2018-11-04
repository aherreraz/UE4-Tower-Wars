// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraMovementComponent.h"


UCameraMovementComponent::UCameraMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

float UCameraMovementComponent::GetMovementSensitivity()
{
	// TODO: Verify clamp values
	return FMath::Clamp<float>(SpringArm->TargetArmLength / 100.f, 5.f, 20.f);
}

void UCameraMovementComponent::Initialise(USpringArmComponent * SpringArm)
{
	this->SpringArm = SpringArm;
}

void UCameraMovementComponent::MovementX(float axisValue)
{
	if (!SpringArm)
		return;

	FVector MovementVector = FVector(axisValue * GetMovementSensitivity() * CurrentMovementMultiplier, 0.f, 0.f);
	FVector CameraLocation = GetOwner()->GetActorLocation();
	FVector NewCameraLocation = MovementVector + CameraLocation;
	FString s = NewCameraLocation.ToString();
	//UE_LOG(LogTemp, Warning, TEXT("MovementVector = %s"), *MovementVector.ToString());
	GetOwner()->SetActorLocation(NewCameraLocation, true);
}

void UCameraMovementComponent::MovementY(float axisValue)
{
	if (!SpringArm)
		return;

	FVector MovementVector = FVector(0.f, axisValue * GetMovementSensitivity() * CurrentMovementMultiplier, 0.f);
	FVector CameraLocation = GetOwner()->GetActorLocation();
	FVector NewCameraLocation = MovementVector + CameraLocation;
	FString s = NewCameraLocation.ToString();
	//UE_LOG(LogTemp, Warning, TEXT("MovementVector = %s"), *MovementVector.ToString());
	GetOwner()->SetActorLocation(NewCameraLocation, true);
}

void UCameraMovementComponent::ToggleMovementMultiplier(bool activateMultiplier)
{
	if (activateMultiplier)
		CurrentMovementMultiplier = MaxMovementMultiplier;
	else
		CurrentMovementMultiplier = 1.f;
}

void UCameraMovementComponent::Zoom(bool zoomIn)
{
	if (!SpringArm)
		return;

	float zoomDistance = ZoomSensitivity;
	if (zoomIn)
		zoomDistance *= -1;

	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength + zoomDistance, MinArmDistance, MaxArmDistance);
}
