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

int32 ATower::IssueCommand_Implementation(ECommandType CommandType, int32 Value, int32 Gold)
{
	if (CommandType == ECommandType::Upgrade)
	{
		// Invalid Command
		if (Value >= Upgrades.Num())
			return 0;

		int32 UpgradeCost = Upgrades[Value]->GetDefaultObject<ATower>()->GoldCost;

		// Not enough gold to pay upgrade
		if (Gold < UpgradeCost)
			return 0;

		// Upgrade
		ATower* NewTower = nullptr;
		ReplaceTower(Upgrades[Value], &NewTower);
		return UpgradeCost;
	}

	// TODO: Implement selling

	return 0;
}

void ATower::ReplaceTower(TSubclassOf<ATower> NewTowerClass, ATower ** OutNewTower)
{
	ATower* const NewTower = GetWorld()->SpawnActorDeferred<ATower>(NewTowerClass, GetTransform(), nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (NewTower)
	{
		UGameplayStatics::FinishSpawningActor(NewTower, GetTransform());
		ISelectionInterface::Execute_OnSelectionLost(this);
		SetLifeSpan(0.1f);
	}
	*OutNewTower = NewTower;
}
