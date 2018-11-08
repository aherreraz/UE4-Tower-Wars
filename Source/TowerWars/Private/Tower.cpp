// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"

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
