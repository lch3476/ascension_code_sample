// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * Static class with utility functions that can be called from C++
 */
class ASCENSION_API AscensionGameplayStatics
{
public:
	
	static float GetAngleBetweenVectorsInDegree(const FVector& Vector1, const FVector& Vector2);

	static FRotator CalculateTargetRotation(const FVector& From, const FVector& To);

};
