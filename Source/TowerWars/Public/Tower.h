// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerWars.h"
#include "GameFramework/Actor.h"
#include "SelectionInterface.h"
#include "Tower.generated.h"

UCLASS()
class TOWERWARS_API ATower : public AActor, public ISelectionInterface
{
	GENERATED_BODY()

public:

	/* ISelectionInterface Implementation */
	virtual bool OnSelectionGained_Implementation() override;

	virtual bool OnSelectionLost_Implementation() override;

	virtual ESelectedType GetType_Implementation() const override;

	/* Construction */
	UFUNCTION(BlueprintCallable, Category = Tower)
	void ReplaceTower(TSubclassOf<ATower> NewTowerClass);

	void ReplaceTower(TSubclassOf<ATower> NewTowerClass, ATower** OutNewTower);


protected:
	UPROPERTY(EditDefaultsOnly, Category = Tower)
	int32 GoldCost;
};
