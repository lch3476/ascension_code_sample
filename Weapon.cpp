// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Components/BoxComponent.h"

AWeapon::AWeapon()
{
}

void AWeapon::BeginPlay()
{
}

FWeaponStatus AWeapon::GetStatus()
{
	return Status;
}