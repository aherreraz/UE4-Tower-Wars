// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerWarsPlayerController.h"
#include "Engine/World.h"
#include "TowerWarsGameState.h"
#include "TowerWarsPlayerState.h"
#include "SelectionInterface.h"
#include "CommandInterface.h"


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

void ATowerWarsPlayerController::IssueCommand(ECommandType CommandType, int32 Value)
{
	ATowerWarsGameState* const GameState = GetWorld()->GetGameState<ATowerWarsGameState>();
	ATowerWarsPlayerState* const PlayerState = GetPlayerState<ATowerWarsPlayerState>();

	if (GameState->GamePhase == EGamePhase::Building)
	{
		if (ISelectionInterface::Execute_GetType(SelectedActor.Get()) == ESelectedType::Tower)
		{
			int32 GoldCost;
			if (CommandType == ECommandType::AnyButSell)
				GoldCost = ICommandInterface::Execute_IssueCommand(SelectedActor.Get(), ECommandType::Upgrade, Value, PlayerState->Gold, GameState->WaveNumber);
			else if (CommandType == ECommandType::Sell)
				GoldCost = ICommandInterface::Execute_IssueSellCommand(SelectedActor.Get(), PlayerState->Gold, GameState->WaveNumber, GameState->DevaluationPercent);
			PlayerState->IncrementGold(-GoldCost);
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

