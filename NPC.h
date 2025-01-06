// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AscensionCharacter.h"
#include "NPC.generated.h"

UCLASS()
class ASCENSION_API ANPC : public AAscensionCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class UBehaviorTree* GetBehaviorTree() const;

	class APatrolPath* GetPatrolPath() const;

	void SetRotationToPlayer(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void SetShouldRotateToPlayer(bool ShouldRotate);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAcess = "true"))
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAcess = "true"))
	APatrolPath* PatrolPath;

private:
	bool bShouldRotateToPlayer = false;
};
