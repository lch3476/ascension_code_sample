// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IncrementPathIndex.h"

#include "NPCAIController.h"
#include "PatrolPath.h"
#include "NPC.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_IncrementPathIndex::UBTTask_IncrementPathIndex(FObjectInitializer const& ObjectInitializer)
	: UBTTask_BlackboardBase(ObjectInitializer)
{
	NodeName = TEXT("Increment Path Index");
}

EBTNodeResult::Type UBTTask_IncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const ANPCAIController* NPCController = Cast<ANPCAIController>(OwnerComp.GetAIOwner());
	if (NPCController != nullptr)
	{
		const ANPC* Npc = Cast<ANPC>(NPCController->GetPawn());
		if (Npc != nullptr)
		{
			UBlackboardComponent* const BlackBoardComponent = OwnerComp.GetBlackboardComponent();
			if (BlackBoardComponent != nullptr)
			{
				const int32 PatrolPathSize = Npc->GetPatrolPath()->Size();
				const int32 MinIndex = 0;
				const int32 MaxIndex = PatrolPathSize;
				int32 Index = BlackBoardComponent->GetValueAsInt(GetSelectedBlackboardKey());

				if (bBiDirectional)
				{
					if (Index >= MaxIndex && Direction == EDirectionType::FORWARD)
					{
						Direction = EDirectionType::REVERSE;
					}
					else if (Index == MinIndex && Direction == EDirectionType::REVERSE)
					{
						Direction = EDirectionType::FORWARD;
					}
				}

				BlackBoardComponent->SetValueAsInt(GetSelectedBlackboardKey(),
					(Direction == EDirectionType::FORWARD ? ++Index : --Index) % PatrolPathSize);

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return  EBTNodeResult::Succeeded;
			}
		}
	}
	return  EBTNodeResult::Failed;
}
