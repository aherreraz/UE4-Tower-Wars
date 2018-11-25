// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerWars.h"
#include "GameFramework/Actor.h"
#include "SelectionInterface.h"
#include "CommandInterface.h"
#include "Tower.generated.h"

UCLASS()
class TOWERWARS_API ATower : public AActor, public ISelectionInterface, public ICommandInterface
{
	GENERATED_BODY()

public:

	/* ISelectionInterface Implementation */
	virtual bool OnSelectionGained_Implementation() override;

	virtual bool OnSelectionLost_Implementation() override;

	virtual ESelectedType GetType_Implementation() const override;

	/* ICommandInterface Implementation */
	virtual int32 IssueCommand_Implementation(ECommandType CommandType, int32 Value, int32 Gold, int32 Wave) override;

	virtual int32 IssueSellCommand_Implementation(int32 Gold, int32 Wave, int32 DevaluationPercent) override;

	/* Construction */

	void ReplaceTower(TSubclassOf<ATower> NewTowerClass, ATower** OutNewTower);


protected:
	UPROPERTY(EditDefaultsOnly, Category = Tower)
	int32 GoldCost;

	UPROPERTY(EditDefaultsOnly, Category = Tower)
	TSubclassOf<ATower> EmptyBuilding;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Tower)
	TArray< TSubclassOf<ATower> > Upgrades;

	// TODO: Calc Sale Cost
	int32 WaveBuilt;
	int32 TotalValue;
	int32 DevaluedValue;
};
