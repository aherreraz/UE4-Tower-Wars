// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Public/CameraMovementComponent.h"
#include "TowerWarsPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOWERWARS_API ATowerWarsPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = Camera)
	UCameraMovementComponent* MovementComponent = nullptr;

	virtual void BeginPlay() override;
	
private:
	UCameraMovementComponent* GetCameraMovementComponent();
};
