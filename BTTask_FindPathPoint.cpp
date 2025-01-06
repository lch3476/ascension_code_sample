// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPathPoint.h"

#include "NPC.h"
#include "NPCAIController.h"
#include "PatrolPath.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPathPoint::UBTTask_FindPathPoint(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Path Point");
}

EBTNodeResult::Type UBTTask_FindPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackBoardComponent = OwnerComp.GetBlackboardComponent();
	if (BlackBoardComponent != nullptr)
	{
		const int32 Index = BlackBoardComponent->GetValueAsInt(GetSelectedBlackboardKey());

		const ANPCAIController* NPCController = Cast<ANPCAIController>(OwnerComp.GetAIOwner());
		if (NPCController != nullptr)
		{
			const ANPC* Npc = Cast<ANPC>(NPCController->GetPawn());
			if (Npc != nullptr)
			{
				FVector Path = Npc->GetPatrolPath()->GetPath(Index);

				FVector PathGlobal = Npc->GetPatrolPath()->GetActorTransform().TransformPosition(Path);
				BlackBoardComponent->SetValueAsVector(PathVectorKey.SelectedKeyName, PathGlobal);
				
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
