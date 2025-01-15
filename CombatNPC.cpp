// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatNPC.h"

#include "CombatComponent.h"
#include "Weapon.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "AscensionEnemyHUD.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/CharacterMovementComponent.h"


ACombatNPC::ACombatNPC()
	:CombatSystem(CreateDefaultSubobject<UCombatComponent>(TEXT("Combat Component")))
{
}

void ACombatNPC::BeginPlay()
{
	Super::BeginPlay();
	EquippedWeapon = Cast<AWeapon>(SpawnEquipment(WeaponClass, TEXT("weapon_socket")));
	Widget = Cast<UAscensionEnemyHUD>(HUD->GetWidget());
	UpdateHealthWidget();
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
	StopAnimMontage();
	GetCharacterMovement()->DisableMovement();
	AAIController* AIController = Cast<AAIController>(GetController());
	EquippedWeapon->CleanOwner();
	if (AIController != nullptr)
	{
		AIController->GetBrainComponent()->StopLogic(TEXT("Death"));
	}
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle,
		[this]() {  EquippedWeapon->Destroy(); Destroy(); },
		7.0f,
		false);
}


AWeapon* ACombatNPC::GetWeapon()
{
	return EquippedWeapon;
}
