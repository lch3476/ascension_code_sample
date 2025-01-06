// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBehaviorState.h"

FCharacterBehaviorState::FCharacterBehaviorState()
	: bIsAttacking(false),
	bCanAttack(true),
	bCanMove(true),
	bIsRunning(false),
	bIsInCombat(false),
	bIsSheath(true),
	bIsRolling(false)
{
}

FCharacterBehaviorState::~FCharacterBehaviorState()
{
}
