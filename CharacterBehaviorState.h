// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBehaviorState.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCharacterBehaviorState
{
	GENERATED_BODY()

public:

	FCharacterBehaviorState();
	~FCharacterBehaviorState();

	UPROPERTY(BlueprintReadWrite)
	bool bIsAttacking;

	UPROPERTY(BlueprintReadWrite)
	bool bCanAttack;

	UPROPERTY(BlueprintReadWrite)
	bool bCanMove;

	UPROPERTY(BlueprintReadWrite)
	bool bIsRunning;

	UPROPERTY(BlueprintReadWrite)
	bool bIsInCombat;

	UPROPERTY(BlueprintReadWrite)
	bool bIsSheath;

	UPROPERTY(BlueprintReadWrite)
	bool bIsRolling;

	UPROPERTY(BlueprintReadWrite)
	bool bIsDead;
};