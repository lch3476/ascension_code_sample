// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPCAIController.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Random Location In NavMesh";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ANPCAIController* const AIController = Cast<ANPCAIController>(OwnerComp.GetAIOwner()))
	{
		if (APawn* const NPCPawn = AIController->GetPawn())
		{
			auto const Origin = NPCPawn->GetActorLocation();

			if (UNavigationSystemV1* const NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation Location;
				if (NavigationSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Location.Location);
				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
