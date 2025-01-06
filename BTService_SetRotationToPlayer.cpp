// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetRotationToPlayer.h"

#include "NPCAIController.h"
#include "NPC.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UBTService_SetRotationToPlayer::UBTService_SetRotationToPlayer()
{
	NodeName = TEXT("Set Rotation To Player");
}

void UBTService_SetRotationToPlayer::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANPCAIController* const NPCAIController = Cast<ANPCAIController>(OwnerComp.GetAIOwner());
	if (NPCAIController != nullptr)
	{
		ANPC* const Npc = Cast<ANPC>(NPCAIController->GetPawn());
		if (Npc != nullptr)
		{
			ACharacter* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			if (Player != nullptr)
			{
				FVector Direction = Player->GetActorLocation() - Npc->GetActorLocation();
				Direction.Z = 0;

				FRotator TargetRotation = UKismetMathLibrary::MakeRotFromX(Direction);

				Npc->SetActorRotation(TargetRotation);
			}
		}
	}
}
