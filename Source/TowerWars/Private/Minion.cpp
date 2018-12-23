// Fill out your copyright notice in the Description page of Project Settings.

#include "Minion.h"

// Sets default values
AMinion::AMinion()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMinion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMinion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AMinion::OnSelectionGained_Implementation()
{
	return true;
}

bool AMinion::OnSelectionLost_Implementation()
{
	return true;
}

ESelectedType AMinion::GetType_Implementation() const
{
	return ESelectedType::Minion;
}

// Called to bind functionality to input
void AMinion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}