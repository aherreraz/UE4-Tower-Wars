// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerWarsPlayerController.h"
#include "SelectionInterface.h"

void ATowerWarsPlayerController::BeginPlay()
{
	Super::BeginPlay();
	MovementComponent = GetCameraMovementComponent();
}

AActor * ATowerWarsPlayerController::GetSelectableTarget()
{
	FHitResult hit;
	if (GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(TRACING_SELECTION), false, hit))
	{
		// TODO: only select allied building or enemy minions
		return hit.GetActor();
	}
	return NULL;
}

void ATowerWarsPlayerController::SetSelectedActor(AActor * NewSelectedActor)
{
	if (SelectedActor != NewSelectedActor)
	{
		// Unselect current selection
		AActor* const OldSelection = SelectedActor.Get();
		if (OldSelection && OldSelection->GetClass()->ImplementsInterface(USelectionInterface::StaticClass()))
			if (ISelectionInterface::Execute_OnSelectionLost(OldSelection))
				SelectedActor = NULL;

		// Select new actor
		if (!SelectedActor.IsValid())
		{
			if (NewSelectedActor && NewSelectedActor->GetClass()->ImplementsInterface(USelectionInterface::StaticClass()))
				if (ISelectionInterface::Execute_OnSelectionGained(NewSelectedActor))
					SelectedActor = NewSelectedActor;
		}
	}
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

