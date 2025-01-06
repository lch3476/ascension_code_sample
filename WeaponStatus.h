// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponStatus.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FWeaponStatus
{
	GENERATED_BODY()

public:
	FWeaponStatus();
	~FWeaponStatus();

	UPROPERTY(EditAnywhere)
	float ATK;

	UPROPERTY(EditAnywhere)
	float Range;
};