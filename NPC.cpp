// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

#include "PatrolPath.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "AscensionGameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CreateDefaultSubobject<APatrolPath>(TEXT("Patrol Path"));
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UBehaviorTree* ANPC::GetBehaviorTree() const
{
	return BehaviorTree;
}

APatrolPath* ANPC::GetPatrolPath() const
{
	return PatrolPath;
}

void ANPC::SetRotationToPlayer(float DeltaTime)
{
	if (bShouldRotateToPlayer)
	{
		ACharacter* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		FRotator TargetRotation = AscensionGameplayStatics::CalculateTargetRotation(
			GetActorLocation(),
			Player->GetActorLocation());

		SetActorRotation(FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 5.f));
	}
}

void ANPC::SetShouldRotateToPlayer(bool ShouldRotate)
{
	bShouldRotateToPlayer = ShouldRotate;
}

