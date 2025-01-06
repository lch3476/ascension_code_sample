// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayerLocation.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_FindPlayerLocation::UBTTask_FindPlayerLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Player Location";
}

EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ACharacter* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		FVector PlayerLocation = Player->GetActorLocation();
		if (SearchRandom)
		{
			FNavLocation Location;

			if (UNavigationSystemV1* const NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				if (NavigationSystem->GetRandomPointInNavigableRadius(PlayerLocation, SearchRadius, Location))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerLocation);
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					return EBTNodeResult::Succeeded;
				}
			}
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerLocation);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
