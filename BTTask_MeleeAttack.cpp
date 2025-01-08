// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MeleeAttack.h"

#include "CombatNPC.h"
#include "NPCAIController.h"

//#include "Components/SkeletalMeshComponent.h"
//#include "Animation/AnimInstance.h"
//#include "Animation/AnimMontage.h"
//#include "Engine/World.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
	NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANPCAIController* const AIController = Cast< ANPCAIController>(OwnerComp.GetAIOwner());
	if (AIController != nullptr)
	{
		ACombatNPC* const CombatNPC = Cast<ACombatNPC>(AIController->GetPawn());
		if (CombatNPC != nullptr)
		{
			if (CombatNPC->IsAnimMontageFinished())
			{
				CombatNPC->Execute_MeleeAttack(CombatNPC);
			}
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
