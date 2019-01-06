// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Minion.h"
#include "TWEnums.h"
#include "TowerWarsGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOWERWARS_API ATowerWarsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void InitGameState() override;

private:
	FTimerHandle GamePhaseTimer;
	FTimerHandle SpawnTimer;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Configuration\|Game Phases")
		int32 BuildingTime = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Configuration\|Game Phases")
		int32 DeploymentTime = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Configuration\|Game Phases")
		int32 PlanningTime = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Configuration\|Game Phases")
		float FightingStartDelay = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Configuration\|Game Phases")
		float FightingInterval = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Configuration\|Game Phases")
		TArray<FMinionGroup> Waves;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Configuration\|Starting Values")
		int32 InitialGold = 50;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Configuration\|Starting Values")
		int32 InitialIncome = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Configuration\|Starting Values")
		int32 InitialCastleHealth = 50;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Configuration\|Misc")
		int32 DevaluationPercent = 50;

	UFUNCTION(BlueprintCallable, Category = GamePhases)
		void SetGamePhase(EGamePhase NewGamePhase);

	UFUNCTION(BlueprintCallable, Category = GamePhases)
		void IncreaseWave();

	UFUNCTION(BlueprintCallable, Category = GamePhases)
		void SpawnMinions(int32 Wave, int32 MinionLevel);
};
