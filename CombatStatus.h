// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatStatus.generated.h"
/**
 * 
 */
USTRUCT(Atomic, BlueprintType)
struct FCombatStatus
{
	GENERATED_BODY()

public:

	FCombatStatus();
	~FCombatStatus();

	UPROPERTY(EditAnywhere)
	float MaxHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float HP;

	UPROPERTY(EditAnywhere)
	float MaxStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Stamina;

	UPROPERTY(EditAnywhere)
	float StaminaRegenerationRate;

	UPROPERTY(EditAnywhere)
	int32 Strength;

	UPROPERTY(EditAnywhere)
	int32 Endurance;
};