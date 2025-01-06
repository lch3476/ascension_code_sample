// Fill out your copyright notice in the Description page of Project Settings.


#include "AscensionGameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

float AscensionGameplayStatics::GetAngleBetweenVectorsInDegree(const FVector& Vector1, const FVector& Vector2)
{
	float DotProduct = Vector1.Dot(Vector2);
	float CosTheta = DotProduct / (Vector1.Length() * Vector2.Length());
	float ThetaInDegree = FMath::RadiansToDegrees(FMath::Acos(CosTheta));
	
	return ThetaInDegree;
}

FRotator AscensionGameplayStatics::CalculateTargetRotation(const FVector& From, const FVector& To)
{
	FVector Direction = To - From;
	Direction.Z = 0;

	FRotator TargetRotation = UKismetMathLibrary::MakeRotFromX(Direction);

	return TargetRotation;
}
