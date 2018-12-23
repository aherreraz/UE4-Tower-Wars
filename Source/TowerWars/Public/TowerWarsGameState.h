// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Minion.h"
#include "TWEnums.h"
#include "TowerWarsGameState.generated.h"

/**
 * 
 */
UCLASS()
class TOWERWARS_API ATowerWarsGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = GamePhases)
	EGamePhase GamePhase;

	UPROPERTY(BlueprintReadOnly, Category = GamePhases)
	int32 WaveNumber;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameConfiguration)
	int32 DevaluationPercent = 30;

private:
	FTimerHandle GamePhaseTimer;
	FTimerHandle SpawnTimer;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GamePhases)
	int32 BuildingTime = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GamePhases)
	int32 DeploymentTime = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GamePhases)
	int32 PlanningTime = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameConfiguration)
	int32 InitialGold = 50;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameConfiguration)
	int32 InitialIncome = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameConfiguration)
	int32 InitialCastleHealth = 50;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameConfiguration)
	TArray<FMinionGroup> Waves;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameConfiguration)
	float SpawnDelay = 1.0f;

	UFUNCTION(BlueprintCallable, Category = GamePhases)
	void SetGamePhase(EGamePhase NewGamePhase);

	UFUNCTION(BlueprintCallable, Category = GamePhases)
	void IncreaseWave();

	UFUNCTION(BlueprintCallable, Category = GamePhases)
	void SpawnMinions(int32 Wave, int32 MinionLevel);
};
