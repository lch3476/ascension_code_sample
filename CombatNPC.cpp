// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatNPC.h"

#include "CombatComponent.h"
#include "Weapon.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "AscensionEnemyHUD.h"


ACombatNPC::ACombatNPC()
	:CombatSystem(CreateDefaultSubobject<UCombatComponent>(TEXT("Combat Component")))
{
}

void ACombatNPC::BeginPlay()
{
	Super::BeginPlay();
	EquippedWeapon = Cast<AWeapon>(SpawnEquipment(WeaponClass, TEXT("weapon_socket")));
	if (Cast<UAscensionEnemyHUD>(HUD->GetWidget()) != nullptr)	UE_LOG(LogTemp, Warning, TEXT("casting valid"))
	Widget = Cast<UAscensionEnemyHUD>(HUD->GetWidget());
}

void ACombatNPC::UpdateHealthWidget()
{
	if (Widget != nullptr && CombatSystem != nullptr)
	{
		Widget->SetHealthPercent(CombatSystem->GetHealth() / CombatSystem->GetMaxHealth());
	}
}


void ACombatNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetRotationToPlayer(DeltaTime);
	UpdateHealthWidget();
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


AWeapon* ACombatNPC::GetWeapon()
{
	return EquippedWeapon;
}
