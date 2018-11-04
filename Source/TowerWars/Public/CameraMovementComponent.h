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

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(USpringArmComponent* SpringArm);

	UFUNCTION(BlueprintCallable, Category = Camera)
	void MovementX(float axisValue);

	UFUNCTION(BlueprintCallable, Category = Camera)
	void MovementY(float axisValue);

	UFUNCTION(BlueprintCallable, Category = Camera)
	void SetMovementMultiplier(float movementMultiplier);

private:
	USpringArmComponent* SpringArm;
	float MovementMultiplier = 1.f;
	float GetMovementSensitivity();
};
