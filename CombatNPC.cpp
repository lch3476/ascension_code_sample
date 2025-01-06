// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatNPC.h"

#include "CombatComponent.h"
#include "Weapon.h"


ACombatNPC::ACombatNPC()
{
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat Component"));
}

void ACombatNPC::BeginPlay()
{
	Super::BeginPlay();
	EquippedWeapon = Cast<AWeapon>(SpawnEquipment(WeaponClass, TEXT("weapon_socket")));
}


void ACombatNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetRotationToPlayer(DeltaTime);
}

void ACombatNPC::MeleeAttack_Implementation()
{
	const int32 RandomIndex = FMath::RandRange(0, AttackMontages.Num() - 1);
	PlayAnimMontage(AttackMontages[RandomIndex]);
	/*if (CombatComponent != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("CombatComponentValid"));
		const int32 RandomIndex = FMath::RandRange(0, AttackMontages.Num());
		CombatComponent->Attack(AttackMontages[RandomIndex]);
	}
	UE_LOG(LogTemp, Warning, TEXT("In MeleeAttack_Implementation"));*/
}

void ACombatNPC::DashAttack_Implementation()
{
}

void ACombatNPC::OnDeath()
{
}

void ACombatNPC::OnDamaged()
{
}
