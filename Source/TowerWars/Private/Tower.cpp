// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "SelectionInterface.h"

bool ATower::OnSelectionGained_Implementation()
{
	return true;
}

bool ATower::OnSelectionLost_Implementation()
{
	return true;
}

ESelectedType ATower::GetType_Implementation() const
{
	return ESelectedType::Tower;
}

void ATower::ReplaceTower(TSubclassOf<ATower> NewTowerClass)
{
	ATower* NewTower = nullptr;
	return ReplaceTower(NewTowerClass, &NewTower);
}

void ATower::ReplaceTower(TSubclassOf<ATower> NewTowerClass, ATower ** OutNewTower)
{
	// TODO: Check cost
	ATower* const NewTower = GetWorld()->SpawnActorDeferred<ATower>(NewTowerClass, GetTransform(), nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (NewTower)
	{
		UGameplayStatics::FinishSpawningActor(NewTower, GetTransform());
		ISelectionInterface::Execute_OnSelectionLost(this);
		SetLifeSpan(0.1f);
	}
	*OutNewTower = NewTower;
}
