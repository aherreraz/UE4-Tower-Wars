// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TWEnums.h"
#include "CommandInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCommandInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOWERWARS_API ICommandInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/** Returns gold spent */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Command)
	int32 IssueCommand(ECommandType CommandType, int32 Value, int32 Gold, int32 Wave);

	/** Returns gold spent */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Command)
	int32 IssueSellCommand(int32 Gold, int32 Wave, int32 DevaluationPercent);
};
