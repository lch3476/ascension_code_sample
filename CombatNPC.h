// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC.h"
#include "CombatInterface.h"

#include "CombatNPC.generated.h"

/**
 * 
 */
UCLASS()
class ASCENSION_API ACombatNPC : public ANPC, public ICombatInterface
{
	GENERATED_BODY()
	
public:
	ACombatNPC();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MeleeAttack_Implementation() override;
	void DashAttack_Implementation() override;
	void OnDeath() override;
	void OnDamaged() override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Equipment")
	TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AWeapon* EquippedWeapon;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UCombatComponent* CombatComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TArray<class UAnimMontage*> AttackMontages;

};
