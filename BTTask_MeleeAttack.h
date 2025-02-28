// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class ASCENSION_API UBTTask_MeleeAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_MeleeAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
