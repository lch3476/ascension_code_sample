// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "EquipableItem.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class ASCENSION_API AEquipableItem : public AItem
{
	GENERATED_BODY()

	public:
		virtual void OnEquip() PURE_VIRTUAL(AEquipableItem::OnEquip, );
};
