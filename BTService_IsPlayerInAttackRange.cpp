// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsPlayerInAttackRange.h"

#include "NPCAIController.h"
#include "NPC.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_IsPlayerInAttackRange::UBTService_IsPlayerInAttackRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player In Attack Range");
}

void UBTService_IsPlayerInAttackRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const ANPCAIController* const NPCAIController = Cast<ANPCAIController>(OwnerComp.GetAIOwner());
	const ANPC* const Npc = Cast<ANPC>(NPCAIController->GetPawn());
	const ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), Npc->GetDistanceTo(Player) <= Range);
}
