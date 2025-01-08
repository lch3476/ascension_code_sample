// Fill out your copyright notice in the Description page of Project Settings.


#include "AscensionPlayerHUD.h"

#include "Components/ProgressBar.h"

void UAscensionPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UAscensionPlayerHUD::SetHealthPercent(float Percent)
{
	if (HealthProgressBar != nullptr)
	{
		HealthProgressBar->SetPercent(Percent);
	}
}

void UAscensionPlayerHUD::SetStaminaPercent(float Percent)
{
	if (StaminaProgressBar != nullptr)
	{
		StaminaProgressBar->SetPercent(Percent);
	}
}
