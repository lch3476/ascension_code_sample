// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "NPC.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Ascender.h"

ANPCAIController::ANPCAIController(FObjectInitializer const& ObjectInitializer)
{
	SetupPerceptionSystem();
}

void ANPCAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ANPC* const Npc = Cast<ANPC>(InPawn))
	{
		if (UBehaviorTree* const BehaviorTree = Npc->GetBehaviorTree())
		{
			UBlackboardComponent* BlackBoardComponent;
			UseBlackboard(BehaviorTree->BlackboardAsset, BlackBoardComponent);
			Blackboard = BlackBoardComponent;
			RunBehaviorTree(BehaviorTree);
		}
	}
}

void ANPCAIController::SetupPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig != nullptr)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component")));
		SightConfig->SightRadius = 1000.f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 1000.f;
		SightConfig->PeripheralVisionAngleDegrees = 135.f;
		SightConfig->SetMaxAge(5.f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ANPCAIController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

void ANPCAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	if (AAscender* const Player = Cast<AAscender>(Actor))
	{
		GetBlackboardComponent()->SetValueAsBool(TEXT("CanSeePlayer"), Stimulus.WasSuccessfullySensed());
	}
}
