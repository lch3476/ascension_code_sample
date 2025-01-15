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
#include "Components/CapsuleComponent.h"
#include "CharacterBehaviorState.h"


// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
	: OwnerCharacter(Cast<AAscensionCharacter>(GetOwner()))
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	Status.HP = Status.MaxHP;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UCombatComponent::OnDamaged);
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCombatComponent::Attack(UAnimMontage* AttackAnimMontage)
{
	if (AttackAnimMontage != nullptr)
	{
		OwnerCharacter->SetIsAttacking(true);
		OwnerCharacter->SetCanMove(false);
		OwnerCharacter->SetCanAttack(false);
		float Length = OwnerCharacter->PlayAnimMontage(AttackAnimMontage);
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
		if (!OwnerCharacter->GetIsDead())
		{
			ICombatInterface* Attacker = Cast<ICombatInterface>(DamageCauser);
			if (Attacker != nullptr)
			{
				AWeapon* Weapon = Attacker->GetWeapon();
				if (Weapon != nullptr)
				{
					float DamageAmount = FMath::Clamp(Weapon->GetStatus().ATK, 0.0f, GetHealth());
					SetHealth(GetHealth() - DamageAmount);

					ICombatInterface* DamagedCharacter = Cast<ICombatInterface>(OwnerCharacter);
					if (DamagedCharacter != nullptr)
					{
						DamagedCharacter->UpdateHealthWidget();
					}
					OwnerCharacter->StopAnimMontage(OwnerCharacter->GetCurrentMontage());
					OwnerCharacter->PlayRandomMontage(DamagedAnimMontages);

					if (GetHealth() <= 0.0f)
					{
						OnDeath();
					}
				}
			}
		}
	}
}

void UCombatComponent::OnDeath()
{
	ICombatInterface* DeadCharacter = Cast<ICombatInterface>(OwnerCharacter);
	if (DeadCharacter != nullptr 
		&& OwnerCharacter != nullptr)
	{
		OwnerCharacter->SetIsDead(true);
		OwnerCharacter->SetActorTickEnabled(false);
		DeadCharacter->OnDeath();
		OwnerCharacter->PlayAnimMontage(DeathAnimMontage);
		OwnerCharacter->GetBehaviorState()->bIsDead = true;
		UCapsuleComponent* Capsule = OwnerCharacter->GetCapsuleComponent();
		if (Capsule != nullptr)
		{
			Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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

void UCombatComponent::StaminaRegenerate(float DeltaTime)
{
	if (!OwnerCharacter->IsAnimMontagePlaying())
	{
		float NewStamina = GetStamina() + Status.StaminaRegenerationRate * DeltaTime;
		NewStamina = FMath::Clamp(NewStamina, 0.0f, GetMaxStamina());
		SetStamina(NewStamina);
	}
}

void UCombatComponent::DepleteStamina()
{
	float NewStamina = GetStamina() - Status.MinStaminaForAction;
	NewStamina = FMath::Clamp(NewStamina, 0.0f, GetMaxStamina());
	SetStamina(NewStamina);
}

bool UCombatComponent::HasEnoughStamina()
{
	return GetStamina() >= Status.MinStaminaForAction;
}

