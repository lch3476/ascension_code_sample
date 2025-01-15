// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipableItem.h"

void AEquipableItem::CleanOwner()
{
	SetOwner(nullptr);
}
