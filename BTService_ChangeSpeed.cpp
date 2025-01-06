// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ChangeSpeed.h"

#include "NPC.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTService_ChangeSpeed::UBTService_ChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Change Speed");
}

void UBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController != nullptr)
	{
		ANPC* Npc = Cast<ANPC>(AIController->GetPawn());
		if (Npc != nullptr)
		{
			Npc->GetCharacterMovement()->MaxWalkSpeed = Speed;
		}
	}
}
