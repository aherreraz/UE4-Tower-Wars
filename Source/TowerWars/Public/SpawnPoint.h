// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TWEnums.h"
#include "SpawnPoint.generated.h"

UCLASS()
class TOWERWARS_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();

	UPROPERTY(EditDefaultsOnly, Category = Spawn)
	FVector SpawnOffset;

	UFUNCTION(BlueprintCallable, Category = Spawn)
	FVector GetSpawnLocation() const;
};

USTRUCT(BlueprintType)
struct FSpawnPointLocation
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnPoint)
		ESpawnPointLocation Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnPoint)
		int32 x;
};