// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatStatus.h"

FCombatStatus::FCombatStatus()
	:MaxHP(100.f),
	HP(MaxHP),
	MaxStamina(100.f),
	Stamina(MaxStamina),
	StaminaRegenerationRate(20.f),
	MinStaminaForAction(20.f),
	Strength(10),
	Endurance(10)
{
}

FCombatStatus::~FCombatStatus()
{
}
