// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatNPC.h"
#include "DarkKnight.generated.h"

/**
 * 
 */
UCLASS()
class ASCENSION_API ADarkKnight : public ACombatNPC
{
	GENERATED_BODY()

public:
	ADarkKnight();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MeleeAttack_Implementation() override;
	void DashAttack_Implementation() override;
	void OnDeath() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
