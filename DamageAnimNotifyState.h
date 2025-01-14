// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "DamageAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class ASCENSION_API UDamageAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation
		, const FAnimNotifyEventReference& EventReference) override;

private:
	bool bIsHit = false;
};
