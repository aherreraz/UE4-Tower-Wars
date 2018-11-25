// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerWarsPlayerState.h"

void ATowerWarsPlayerState::Initialize(int32 InitialGold, int32 InitialIncome, int32 InitialCastleHealth)
{
	Gold = InitialGold;
	Income = InitialIncome;
	CastleHealth = InitialCastleHealth;
}

void ATowerWarsPlayerState::PayIncome()
{
	Gold += Income;
}
