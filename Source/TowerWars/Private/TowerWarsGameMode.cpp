// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerWarsGameMode.h"
#include "TimerManager.h"
#include "EngineUtils.h"
#include "TowerWarsGameState.h"
#include "TowerWarsPlayerState.h"
#include "SpawnPoint.h"

void ATowerWarsGameMode::InitGameState()
{
	Super::InitGameState();
	/*ATowerWarsGameState* const TowerWarsGameState = GetGameState<ATowerWarsGameState>();
	if (TowerWarsGameState)
	{
		TowerWarsGameState->WaveNumber = 1;
		TowerWarsGameState->DevaluationPercent = DevaluationPercent;
		SetGamePhase(EGamePhase::Building);
		
		for (APlayerState* playerState : TowerWarsGameState->PlayerArray)
			Cast<ATowerWarsPlayerState>(playerState)->Initialize(InitialGold, InitialIncome, InitialCastleHealth);
	}*/
}

void ATowerWarsGameMode::BeginPlay()
{
	Super::BeginPlay();
	ATowerWarsGameState* const TowerWarsGameState = GetGameState<ATowerWarsGameState>();
	if (TowerWarsGameState)
	{
		TowerWarsGameState->WaveNumber = 1;
		TowerWarsGameState->DevaluationPercent = DevaluationPercent;
		SetGamePhase(EGamePhase::Building);

		for (APlayerState* playerState : TowerWarsGameState->PlayerArray)
			Cast<ATowerWarsPlayerState>(playerState)->Initialize(InitialGold, InitialIncome, InitialCastleHealth);
	}
}

void ATowerWarsGameMode::SetGamePhase(EGamePhase NewGamePhase)
{
	ATowerWarsGameState* const TowerWarsGameState = GetGameState<ATowerWarsGameState>();
	
	if (TowerWarsGameState)
	{
		TowerWarsGameState->GamePhase = NewGamePhase;
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
				int32 Wave = TowerWarsGameState->WaveNumber % Waves.Num();
				int32 MinionLevel = TowerWarsGameState->WaveNumber / Waves.Num();
				TimerDel.BindUFunction(this, FName("SpawnMinions"), Wave, MinionLevel);
				GetWorldTimerManager().SetTimer(SpawnTimer, TimerDel, FightingInterval, true, FightingStartDelay);
				//GetWorldTimerManager().SetTimer(GamePhaseTimer, this, &ATowerWarsGameState::IncreaseWave, PlanningTime, false);
			}
			break;
		}
		// TODO: Notify players if needed
	}
}

void ATowerWarsGameMode::IncreaseWave()
{
	ATowerWarsGameState* const TowerWarsGameState = GetGameState<ATowerWarsGameState>();
	if (TowerWarsGameState)
	{
		// TODO: Generate wave
		TowerWarsGameState->WaveNumber++;
		SetGamePhase(EGamePhase::Building);

		// Pay income to players
		for (APlayerState* playerState : TowerWarsGameState->PlayerArray)
			Cast<ATowerWarsPlayerState>(playerState)->PayIncome();
	}
}

void ATowerWarsGameMode::SpawnMinions(int32 Wave, int32 MinionLevel)
{
	UE_LOG(LogTemp, Warning, TEXT("Start Wave = %d Level = %d"), Wave, MinionLevel);
	int32 SpawnedActors = 0;
	for (TActorIterator<ASpawnPoint> SpawnIt(GetWorld()); SpawnIt; ++SpawnIt)
	{
		for (TPair< TSubclassOf<AMinion>, int32>& Minion : Waves[Wave].Minions)
		{
			if (Minion.Value > 0)
			{
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