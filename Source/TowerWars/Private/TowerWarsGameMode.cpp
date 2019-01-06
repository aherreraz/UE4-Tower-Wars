// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerWarsGameMode.h"
#include <vector>
#include "TimerManager.h"
#include "EngineUtils.h"
#include "TowerWarsGameState.h"
#include "TowerWarsPlayerState.h"


void ATowerWarsGameMode::BeginPlay()
{
	Super::BeginPlay();
	ATowerWarsGameState* const TowerWarsGameState = GetGameState<ATowerWarsGameState>();
	if (TowerWarsGameState)
	{
		CreateMap();
		TowerWarsGameState->WaveNumber = 1;
		TowerWarsGameState->DevaluationPercent = DevaluationPercent;
		SetGamePhase(EGamePhase::Building);

		for (APlayerState* playerState : TowerWarsGameState->PlayerArray)
			Cast<ATowerWarsPlayerState>(playerState)->Initialize(InitialGold, InitialIncome, InitialCastleHealth);
	}
}

void ATowerWarsGameMode::CreateMap()
{
	ATowerWarsGameState* const TowerWarsGameState = GetGameState<ATowerWarsGameState>();

	if (!EmptyBlockClass || !SpawnPointClass || !CastleClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Map couldn't be created, verify map cofiguration parameters are set"));
	}
	for (APlayerState* playerState : TowerWarsGameState->PlayerArray)
	{
		ATowerWarsPlayerState* twPlayerState = Cast<ATowerWarsPlayerState>(playerState);
		twPlayerState->MapGrid = std::vector< std::vector<int32> >(MapNTiles + 2, std::vector<int32>(MapMTiles + 2, 1));
		//UE_LOG(LogTemp, Warning, TEXT("Grid n = %d; m = %d"), twPlayerState->MapGrid.size(), twPlayerState->MapGrid[0].size());

		//TODO: Implement for multiple players. Currently spawning relative to map origin

		// Spawn Empty Blocks
		for (int32 i = 1; i <= MapNTiles; i++)
		{
			for (int32 j = 1; j <= MapMTiles; j++)
			{
				twPlayerState->MapGrid[i][j] = 0;
				GetWorld()->SpawnActor<ATower>(EmptyBlockClass, FVector(i, j, 0) * TileSize, FRotator::ZeroRotator);
			}
		}

		// Spawn Spawn Points
		for (FSpawnPointLocation spawnPoint : SpawnPoints)
		{
			switch (spawnPoint.Location)
			{
			case ESpawnPointLocation::Top:
				if (spawnPoint.x < MapMTiles)
				{
					twPlayerState->MapGrid[MapNTiles + 1][spawnPoint.x + 1] = 0;
					GetWorld()->SpawnActor<ASpawnPoint>(SpawnPointClass, FVector(MapNTiles + 1, spawnPoint.x + 1, 0) * TileSize, FRotator::ZeroRotator);
				}
				break;
			case ESpawnPointLocation::Left:
				if (spawnPoint.x < MapNTiles)
				{
					twPlayerState->MapGrid[spawnPoint.x + 1][0] = 0;
					GetWorld()->SpawnActor<ASpawnPoint>(SpawnPointClass, FVector(spawnPoint.x + 1, 0, 0) * TileSize, FRotator::ZeroRotator);
				}
				break;
			case ESpawnPointLocation::Right:
				if (spawnPoint.x < MapNTiles)
				{
					twPlayerState->MapGrid[spawnPoint.x + 1][MapMTiles + 1] = 0;
					GetWorld()->SpawnActor<ASpawnPoint>(SpawnPointClass, FVector(spawnPoint.x + 1, MapMTiles + 1, 0) * TileSize, FRotator::ZeroRotator);
				}
				break;
			}
		}

		// Spawn Castle
		GetWorld()->SpawnActor<AActor>(CastleClass, FVector(0, MapMTiles / 2.0f + 1, 0) * TileSize, FRotator::ZeroRotator);
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