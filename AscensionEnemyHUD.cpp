// Fill out your copyright notice in the Description page of Project Settings.


#include "AscensionEnemyHUD.h"

#include "Components/ProgressBar.h"

void UAscensionEnemyHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UAscensionEnemyHUD::SetHealthPercent(float Percent)
{
	if (HealthBar != nullptr)
	{
		HealthBar->SetPercent(Percent);
	}
}
