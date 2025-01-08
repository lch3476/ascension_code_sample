// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Components/BoxComponent.h"

AWeapon::AWeapon()
{
}

void AWeapon::BeginPlay()
{
}

void AWeapon::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("YESs"))
	if (OtherActor != nullptr && OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("YES"))
	}
}
