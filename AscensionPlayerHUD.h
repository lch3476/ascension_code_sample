// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "AscensionPlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class ASCENSION_API UAscensionPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void SetHealthPercent(float Percent);
	void SetStaminaPercent(float Percent);

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", BindWidget))
	class UProgressBar* HealthBar = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", BindWidget))
	class UProgressBar* StaminaBar = nullptr;
};
