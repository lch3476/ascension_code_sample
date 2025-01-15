// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipableItem.h"
#include "WeaponStatus.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class ASCENSION_API AWeapon : public AEquipableItem
{
	GENERATED_BODY()

public:
	AWeapon();
	
	virtual void BeginPlay() override;
	
	FWeaponStatus GetStatus();


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	FWeaponStatus Status;
};
