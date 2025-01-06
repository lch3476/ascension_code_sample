// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPath.generated.h"

UCLASS()
class ASCENSION_API APatrolPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrolPath();

	FVector GetPath(const int index) const;
	int Size() const;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	TArray<FVector> PatrolPaths;
};
