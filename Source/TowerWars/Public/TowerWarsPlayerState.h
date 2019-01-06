// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include <vector>
#include "TowerWarsPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TOWERWARS_API ATowerWarsPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Player Stats\|Main")
		int32 CastleHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Player Stats\|Main")
		int32 Gold;

	UPROPERTY(BlueprintReadOnly, Category = "Player Stats\|Main")
		int32 Income;

	std::vector< std::vector< int32 > > MapGrid;

	void Initialize(int32 InitialGold, int32 InitialIncome, int32 InitialCastleHealth);
	void PayIncome();

	UFUNCTION(BlueprintCallable, Category = MainStats)
		void IncrementGold(int32 Increment);
};
