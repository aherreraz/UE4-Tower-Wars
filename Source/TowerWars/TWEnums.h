#include "TWEnums.generated.h"
#pragma once

UENUM(BlueprintType)
enum class ESelectedType : uint8
{
	None,
	Barracks,
	Tower,
	Minion
};

UENUM(BlueprintType)
enum class EGamePhase : uint8
{
	Building,
	Deployment,
	Planning,
	Fighting
};

UENUM(BlueprintType)
enum class ECommandType : uint8
{
	AnyButSell,
	Upgrade,
	Sell,
	Deploy,
	ChangeAttack
};