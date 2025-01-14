// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

#include "GameFramework/Character.h"
#include "AscensionCharacter.h"
#include "Animation/AnimInstance.h"
#include "Ascender.h"
#include "Components/WidgetComponent.h"
#include "AscensionPlayerHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimMontage.h"
#include "Weapon.h"


// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
	: OwnerCharacter(Cast<AAscensionCharacter>(GetOwner()))
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
	Status.HP = Status.MaxHP;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UCombatComponent::OnDamaged);
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatComponent::Attack(UAnimMontage* AttackAnimMontage)
{
	if (AttackAnimMontage != nullptr)
	{
		OwnerCharacter->SetIsAttacking(true);
		OwnerCharacter->SetCanMove(false);
		OwnerCharacter->SetCanAttack(false);
		float Length = AnimInstance->Montage_Play(AttackAnimMontage);
		FTimerHandle TimerHandle;
		OwnerCharacter->GetWorldTimerManager().SetTimer(
			TimerHandle,
			[this]() {OwnerCharacter->SetIsAttacking(false); },
			Length,
			false
		);
	}
}

void UCombatComponent::ComboAttack(TArray<UAnimMontage*> ComboMontages)
{
	if (ComboMontages.IsValidIndex(CurrentComboIndex))
	{
		UAnimMontage* NextCombo = ComboMontages[CurrentComboIndex];
		if (NextCombo != nullptr)
		{
			Attack(NextCombo);
			CurrentComboIndex++;
		}
	}
}

void UCombatComponent::OnDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamageCauser != nullptr && DamagedActor != nullptr)
	{
		ICombatInterface* Attacker = Cast<ICombatInterface>(DamageCauser);
		if (Attacker != nullptr)
		{
			AWeapon* Weapon = Attacker->GetWeapon();
			if (Weapon != nullptr)
			{
				float DamageAmount = FMath::Clamp(Weapon->GetStatus().ATK, 0.0f, GetHealth());
				SetHealth(GetHealth() - DamageAmount);

				UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();
				if (CurrentMontage != nullptr)
				{
					AnimInstance->Montage_Stop(0.2f, CurrentMontage);
				}

				UAnimMontage* DamagedMontagesToPlay = DamagedMontages[FMath::RandRange(0, DamagedMontages.Num()-1)];
				if (DamagedMontagesToPlay != nullptr)
				{
					AnimInstance->Montage_Play(DamagedMontagesToPlay);
				}
			}
		}
	}
}

void UCombatComponent::ResetCombo()
{
	CurrentComboIndex = 0;
	OwnerCharacter->SetCanAttack(false);
}

float UCombatComponent::GetHealth() const
{
	return Status.HP;
}

float UCombatComponent::GetMaxHealth() const
{
	return Status.MaxHP;
}

void UCombatComponent::SetHealth(const float Health)
{
	Status.HP = Health;
}

float UCombatComponent::GetStamina() const
{
	return Status.Stamina;
}

float UCombatComponent::GetMaxStamina() const
{
	return Status.MaxStamina;
}

void UCombatComponent::SetStamina(const float Stamina)
{
	Status.Stamina = Stamina;
}

