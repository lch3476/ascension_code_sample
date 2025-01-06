// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AscensionCharacter.generated.h"

UCLASS()
class ASCENSION_API AAscensionCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAscensionCharacter();

	UFUNCTION(BlueprintCallable)
	float GetCurrentSpeed();

	UFUNCTION(BlueprintCallable)
	void DisableCharacterMovement(float Delay);

	UFUNCTION(BlueprintCallable)
	void SetCanMove(bool bCanMove);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class AEquipableItem* SpawnEquipment(UClass* EquipmentClass, FName SocketName);

	void SetCharacterMovability(bool bCanMove);
	bool CanMove();
	bool CanAttack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SetIsAttacking(bool bIsAttacking);

	UFUNCTION(BlueprintCallable)
	void SetCanAttack(bool bCanAttack);

	struct FCharacterBehaviorState* GetBehaviorState();

	bool IsAnimMontageFinished();
	bool IsAnimMontagePlaying();
	
protected:

	FCharacterBehaviorState* BehaviorState;
};
