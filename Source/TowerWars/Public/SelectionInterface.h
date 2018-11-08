// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "TowerWars.h"
#include "UObject/Interface.h"
#include "TWEnums.h"
#include "SelectionInterface.generated.h"

UINTERFACE(MinimalAPI)
class USelectionInterface : public UInterface
{
	GENERATED_BODY()
};

class TOWERWARS_API ISelectionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = Selection)
	bool OnSelectionGained();

	UFUNCTION(BlueprintNativeEvent, Category = Selection)
	bool OnSelectionLost();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Selection)
	ESelectedType GetType() const;
};
