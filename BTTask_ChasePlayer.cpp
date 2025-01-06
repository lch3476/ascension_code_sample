// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChasePlayer.h"

#include "NPCAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ANPCAIController* const NPCController = Cast<ANPCAIController>(OwnerComp.GetAIOwner()))
	{
		FVector PlayerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(NPCController, PlayerLocation);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
