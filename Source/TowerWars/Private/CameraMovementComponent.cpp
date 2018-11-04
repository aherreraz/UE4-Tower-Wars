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

	float DeltaMovement = axisValue * GetMovementSensitivity() * CurrentMovementMultiplier;
	GetOwner()->AddActorLocalOffset(DeltaMovement * FVector::ForwardVector, true);
}

void UCameraMovementComponent::MovementY(float axisValue)
{
	if (!SpringArm)
		return;

	float DeltaMovement = axisValue * GetMovementSensitivity() * CurrentMovementMultiplier;
	GetOwner()->AddActorLocalOffset(DeltaMovement * FVector::RightVector, true);
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

void UCameraMovementComponent::ScreenEdgeMovement(FVector2D MousePosition, FVector2D ScreenSize)
{
	// Actor x = -Screen y
	// Actor y = Screen x

	FVector2D ScreenRatio = MousePosition / ScreenSize;
	FVector DeltaMovement(0.f, 0.f, 0.f);
	if (ScreenRatio.Y <= 0.025f)
		DeltaMovement.X = MouseMovementSpeed;
	else if (ScreenRatio.Y >= 0.975f)
		DeltaMovement.X = -MouseMovementSpeed;

	if (ScreenRatio.X <= 0.025f)
		DeltaMovement.Y = -MouseMovementSpeed;
	else if (ScreenRatio.X >= 0.975f)
		DeltaMovement.Y = MouseMovementSpeed;

	GetOwner()->AddActorLocalOffset(DeltaMovement, true);
}
