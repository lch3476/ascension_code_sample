// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_IncrementPathIndex.generated.h"

/**
 * 
 */
UCLASS()
class ASCENSION_API UBTTask_IncrementPathIndex : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

	explicit UBTTask_IncrementPathIndex(FObjectInitializer const& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:
	enum class EDirectionType { FORWARD, REVERSE};

	EDirectionType Direction = EDirectionType::FORWARD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bBiDirectional = false;
};
