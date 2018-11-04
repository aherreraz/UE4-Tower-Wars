// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerWarsPlayerController.h"

void ATowerWarsPlayerController::BeginPlay()
{
	Super::BeginPlay();
	MovementComponent = GetCameraMovementComponent();
}

UCameraMovementComponent * ATowerWarsPlayerController::GetCameraMovementComponent()
{
	APawn* Pawn = GetPawn();
	if (!ensure(Pawn))
	{
		return nullptr;
	}
	return Pawn->FindComponentByClass<UCameraMovementComponent>();
}