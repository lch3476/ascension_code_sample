// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkKnight.h"
#include "Weapon.h"

ADarkKnight::ADarkKnight()
{
	if (CombatComponent != nullptr) UE_LOG(LogTemp, Warning, TEXT("cp darkknight"));
}

void ADarkKnight::BeginPlay()
{
	Super::BeginPlay();
	if (CombatComponent != nullptr) UE_LOG(LogTemp, Warning, TEXT("cp darkknight"));
}

void ADarkKnight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADarkKnight::MeleeAttack_Implementation()
{
	Super::MeleeAttack_Implementation();
}

void ADarkKnight::DashAttack_Implementation()
{
	Super::DashAttack_Implementation();
}

void ADarkKnight::OnDeath()
{
	Super::OnDeath();
}

