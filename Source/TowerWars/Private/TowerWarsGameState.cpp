// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerWarsGameState.h"
#include "TowerWarsPlayerState.h"
#include "TimerManager.h"

void ATowerWarsGameState::BeginPlay()
{
	Super::BeginPlay();

	// Set initial game state
	WaveNumber = 1;
	SetGamePhase(EGamePhase::Building);
	
	for (APlayerState* playerState : PlayerArray)
		Cast<ATowerWarsPlayerState>(playerState)->Initialize(InitialGold, InitialIncome, InitialCastleHealth);

	// Set timer for next phase
	FTimerDelegate TimerDel;
	
}

void ATowerWarsGameState::SetGamePhase(EGamePhase NewGamePhase)
{
	GamePhase = NewGamePhase;
	FTimerDelegate TimerDel;

	switch (NewGamePhase)
	{
	case EGamePhase::Building:
		TimerDel.BindUFunction(this, FName("SetGamePhase"), EGamePhase::Deployment);
		GetWorldTimerManager().SetTimer(GamePhaseTimer, TimerDel, BuildingTime, false);
		break;
	case EGamePhase::Deployment:
		TimerDel.BindUFunction(this, FName("SetGamePhase"), EGamePhase::Planning);
		GetWorldTimerManager().SetTimer(GamePhaseTimer, TimerDel, DeploymentTime, false);
		break;
	case EGamePhase::Planning:
		TimerDel.BindUFunction(this, FName("SetGamePhase"), EGamePhase::Fighting);
		GetWorldTimerManager().SetTimer(GamePhaseTimer, TimerDel, PlanningTime, false);
		break;
	case EGamePhase::Fighting:
		// TODO: remove this, just for testing
		// TODO: Implement listener
		GetWorldTimerManager().SetTimer(GamePhaseTimer, this, &ATowerWarsGameState::IncreaseWave, PlanningTime, false);
		break;
	}
	// TODO: Notify players if needed
}

void ATowerWarsGameState::IncreaseWave()
{
	// TODO: Generate wave
	WaveNumber++;
	SetGamePhase(EGamePhase::Building);

	// Pay income to players
	for (APlayerState* playerState : PlayerArray)
		Cast<ATowerWarsPlayerState>(playerState)->PayIncome();
}
