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
		int32 DevaluationPercent;
};
