// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

FVector ASpawnPoint::GetSpawnLocation() const
{
	return GetActorLocation() + SpawnOffset;
}
