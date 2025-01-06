// Fill out your copyright notice in the Description page of Project Settings.



#include "GameFramework/Character.h"
#include "AscensionCharacter.h"
#include "Animation/AnimInstance.h"
#include "Ascender.h"
#include "Components/WidgetComponent.h"
#include "AscensionPlayerHUD.h"

#include "CombatComponent.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
	: OwnerCharacter(Cast<AAscensionCharacter>(GetOwner()))
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	InitializeWidget();
	UpdateHealthWidget();
	UpdateStaminaWidget();
}

// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
	Status.HP = Status.MaxHP;
}

void UCombatComponent::UpdateHealthWidget()
{
	if (StatusWidget != nullptr)
	{
		StatusWidget->SetHealthPercent(GetHealth() / GetMaxHealth());
	}
}

void UCombatComponent::UpdateStaminaWidget()
{
	if (StatusWidget != nullptr)
	{
		StatusWidget->SetStaminaPercent(GetStamina() / GetMaxStamina());
	}
}

void UCombatComponent::InitializeWidget()
{
	AAscender* const Player = Cast<AAscender>(GetOwner());
	if (Player != nullptr)
	{
		UWidgetComponent* const PlayerHUD = Player->GetPlayerHUD();
		if (PlayerHUD != nullptr)
		{
			StatusWidget = Cast<UAscensionPlayerHUD>(PlayerHUD->GetUserWidgetObject());
		}
	}
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


