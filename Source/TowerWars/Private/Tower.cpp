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

int32 ATower::IssueCommand_Implementation(ECommandType CommandType, int32 Value, int32 Gold, int32 Wave)
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
		NewTower->WaveBuilt = Wave;
		NewTower->TotalValue = TotalValue + NewTower->GoldCost;
		NewTower->DevaluedValue = (Wave == WaveBuilt) ? DevaluedValue : TotalValue;
		return UpgradeCost;
	}
	// TODO: Implement change attack

	return 0;
}

int32 ATower::IssueSellCommand_Implementation(int32 Gold, int32 Wave, int32 DevaluationPercent)
{
	// Must set an empty building
	if (!EmptyBuilding)
		return 0;

	// Cant sell an empty building
	if (TotalValue == 0)
		return 0;

	ATower* NewTower = nullptr;
	ReplaceTower(EmptyBuilding, &NewTower);
	if (WaveBuilt == Wave)
		return (DevaluedValue * DevaluationPercent / 100) - TotalValue;
	
	return TotalValue * (DevaluationPercent - 100) / 100;
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
