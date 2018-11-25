// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerWars.h"
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

	UPROPERTY(BlueprintReadOnly, Category = Selection)
	TWeakObjectPtr<AActor> SelectedActor;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Selection)
	AActor* GetSelectableTarget();

	UFUNCTION(BlueprintCallable, Category = Selection)
	void SetSelectedActor(AActor* NewSelectedActor);

	
	
private:
	UCameraMovementComponent* GetCameraMovementComponent();
};
