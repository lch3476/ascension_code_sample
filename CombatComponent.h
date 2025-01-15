// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatStatus.h"

#include "CombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASCENSION_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

	void Attack(class UAnimMontage* AttackAnimMontage);
	void ComboAttack(TArray<UAnimMontage*> ComboMontages);

	float GetHealth() const;
	float GetMaxHealth() const;
	void SetHealth(const float Health);

	float GetStamina() const;
	float GetMaxStamina() const;
	void SetStamina(const float Stamina);

	void StaminaRegenerate(float DeltaTime);
	void DepleteStamina();
	bool HasEnoughStamina();

	UFUNCTION()
	virtual void OnDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	void OnDeath();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ResetCombo();

	int32 CurrentComboIndex = 0;


private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TArray<class UAnimMontage*> DamagedAnimMontages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FCombatStatus Status;

	class AAscensionCharacter* OwnerCharacter;
};
