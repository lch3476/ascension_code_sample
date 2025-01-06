// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS(Abstract)
class ASCENSION_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Basic Info", meta = (AllowPrivateAccess = "true"))
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Basic Info", meta = (AllowPrivateAccess = "true"))
	FString Description;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic Info", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;
};
