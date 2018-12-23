// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerWarsGameState.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "TowerWarsPlayerState.h"
#include "TimerManager.h"
#include "SpawnPoint.h"

void ATowerWarsGameState::BeginPlay()
{
	Super::BeginPlay();

	// Set initial game state
	WaveNumber = 1;
	SetGamePhase(EGamePhase::Building);
	
	for (APlayerState* playerState : PlayerArray)
		Cast<ATowerWarsPlayerState>(playerState)->Initialize(InitialGold, InitialIncome, InitialCastleHealth);
}

void ATowerWarsGameState::SetGamePhase(EGamePhase NewGamePhase)
{
	UE_LOG(LogTemp, Warning, TEXT("New Game Phase: %d"), int32(NewGamePhase));
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
		if (Waves.Num())
		{
			int32 Wave = WaveNumber % Waves.Num();
			int32 MinionLevel = WaveNumber / Waves.Num();
			TimerDel.BindUFunction(this, FName("SpawnMinions"), Wave, MinionLevel);
			GetWorldTimerManager().SetTimer(SpawnTimer, TimerDel, SpawnDelay, true, SpawnDelay);
			//GetWorldTimerManager().SetTimer(GamePhaseTimer, this, &ATowerWarsGameState::IncreaseWave, PlanningTime, false);
		}
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

void ATowerWarsGameState::SpawnMinions(int32 Wave, int32 MinionLevel)
{
	UE_LOG(LogTemp, Warning, TEXT("Start Wave = %d Level = %d"), Wave, MinionLevel);
	int32 SpawnedActors = 0;
	for (TActorIterator<ASpawnPoint> SpawnIt(GetWorld()); SpawnIt; ++SpawnIt)
	{
		for (TPair< TSubclassOf<AMinion>, int32>& Minion : Waves[Wave].Minions)
		{
			if (Minion.Value > 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("Time to spawn minion"));
				GetWorld()->SpawnActor<AMinion>(Minion.Key, SpawnIt->GetSpawnLocation(), SpawnIt->GetActorRotation());
				Minion.Value--;
				SpawnedActors++;
				break;
			}
		}
	}
	if (SpawnedActors == 0)
		GetWorldTimerManager().ClearTimer(SpawnTimer);
}