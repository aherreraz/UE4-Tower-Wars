// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CameraMovementComponent.generated.h"


UCLASS( ClassGroup=(CameraComponent), meta=(BlueprintSpawnableComponent) )
class TOWERWARS_API UCameraMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCameraMovementComponent();

	UPROPERTY(EditDefaultsOnly, Category = Camera)
	float MaxMovementMultiplier;

	UPROPERTY(EditDefaultsOnly, Category = Camera)
	float ZoomSensitivity;

	UPROPERTY(EditDefaultsOnly, Category = Camera)
	float MinArmDistance;

	UPROPERTY(EditDefaultsOnly, Category = Camera)
	float MaxArmDistance;

	UFUNCTION(BlueprintCallable, Category = Camera)
	void Initialise(USpringArmComponent* SpringArm);

	UFUNCTION(BlueprintCallable, Category = Camera)
	void MovementX(float axisValue);

	UFUNCTION(BlueprintCallable, Category = Camera)
	void MovementY(float axisValue);

	UFUNCTION(BlueprintCallable, Category = Camera)
	void ToggleMovementMultiplier(bool activateMultiplier);

	UFUNCTION(BlueprintCallable, Category = Camera)
	void Zoom(bool zoomIn);

private:
	USpringArmComponent* SpringArm;
	float CurrentMovementMultiplier = 1.f;
	float GetMovementSensitivity();
};
