// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SelectionInterface.h"
#include "Minion.generated.h"



UCLASS()
class TOWERWARS_API AMinion : public ACharacter, public ISelectionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMinion();

	UPROPERTY(EditDefaultsOnly, Category = "Minion\|BaseValues")
	int32 BaseHealth;

	UPROPERTY(EditDefaultsOnly, Category = "Minion\|BaseValues")
	int32 BaseArmor;

	UPROPERTY(EditDefaultsOnly, Category = "Minion\|BaseValues")
	int32 BaseMovementSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Minion\|BaseValues")
	int32 BaseAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Minion\|IncreasedValues")
	int32 HealthPerLevel;

	UPROPERTY(EditDefaultsOnly, Category = "Minion\|IncreasedValues")
	int32 ArmorPerLevel;

	UPROPERTY(EditDefaultsOnly, Category = "Minion\|IncreasedValues")
	int32 MovementSpeedPerLevel;

	UPROPERTY(EditDefaultsOnly, Category = "Minion\|IncreasedValues")
	int32 AttackPerLevel;


	/* ISelectionInterface Implementation */
	virtual bool OnSelectionGained_Implementation() override;

	virtual bool OnSelectionLost_Implementation() override;

	virtual ESelectedType GetType_Implementation() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

USTRUCT(BlueprintType)
struct FMinionGroup
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Minion)
	TMap<TSubclassOf<AMinion>, int32> Minions;
};