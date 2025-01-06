// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetRotationToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ASCENSION_API UBTService_SetRotationToPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_SetRotationToPlayer();
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
