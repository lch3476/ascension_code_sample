// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AscensionGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ASCENSION_API AAscensionGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AAscensionGameModeBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
};
