// Fill out your copyright notice in the Description page of Project Settings.


#include "AscensionCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "EquipableItem.h"
#include "CharacterBehaviorState.h"
#include "Components/WidgetComponent.h"

// Sets default values
AAscensionCharacter::AAscensionCharacter()
	: BehaviorState(new FCharacterBehaviorState()),
	HUD(CreateDefaultSubobject<UWidgetComponent>("HUD"))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (HUD != nullptr) HUD->SetupAttachment(RootComponent);
}

float AAscensionCharacter::GetCurrentSpeed()
{
	return GetVelocity().Size();
}

void AAscensionCharacter::DisableCharacterMovement(float Delay)
{
	SetCharacterMovability(false);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(
		TimerHandle,
		[this]() { this->SetCharacterMovability(true); },
		Delay,
		false);
}

void AAscensionCharacter::SetCanMove(bool bCanMove)
{
	if (BehaviorState != nullptr)
	{
		BehaviorState->bCanMove = bCanMove;
	}
}

UWidgetComponent* AAscensionCharacter::GetHUD()
{
	return HUD;
}

// Called when the game starts or when spawned
void AAscensionCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SetupHUD();
}

AEquipableItem* AAscensionCharacter::SpawnEquipment(UClass* EquipmentClass, FName SocketName)
{
	if (EquipmentClass != nullptr)
	{
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();

		AEquipableItem* Equipment = GetWorld()->SpawnActor<AEquipableItem>(EquipmentClass, SpawnLocation, SpawnRotation);

		if (Equipment != nullptr)
		{
			Equipment->AttachToComponent(
				GetMesh(),
				FAttachmentTransformRules::SnapToTargetIncludingScale,
				SocketName);
			Equipment->SetOwner(this);
			return Equipment;
		}
	}
	return nullptr;
}

void AAscensionCharacter::SetCharacterMovability(bool bCanMove)
{
	UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (MovementComponent != nullptr)
	{
		MovementComponent->SetMovementMode(bCanMove ? MOVE_Walking : MOVE_None);
	}
}

bool AAscensionCharacter::CanMove()
{
	if (BehaviorState != nullptr)
	{
		return BehaviorState->bCanMove;
	}
	return true;
}

bool AAscensionCharacter::CanAttack()
{
	if (BehaviorState != nullptr)
	{
		return BehaviorState->bCanAttack;
	}
	return false;
}

void AAscensionCharacter::SetupHUD()
{
	if (HUD != nullptr)
	{
		TSubclassOf<UUserWidget> WidgetClass = HUD->GetWidgetClass();
		auto* Widget = CreateWidget(GetWorld(), WidgetClass);
		HUD->SetWidget(Widget);
		if (Widget != nullptr)
		{
			Widget->AddToPlayerScreen();
		}
	}
}

float AAscensionCharacter::PlayRandomMontage(TArray<class UAnimMontage*> Montages)
{
	
	UAnimMontage* MontageToPlay = nullptr;
	if (Montages.Num() > 0)
	{
		MontageToPlay = Montages[FMath::RandRange(0, Montages.Num() - 1)];
	}

	float Length = 0.0f;
	if (MontageToPlay != nullptr)
	{
		Length = PlayAnimMontage(MontageToPlay);
	}

	return Length;
}

// Called every frame
void AAscensionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAscensionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAscensionCharacter::SetIsAttacking(bool bIsAttacking)
{
	if (BehaviorState != nullptr)
	{
		BehaviorState->bIsAttacking = bIsAttacking;
	}
}

void AAscensionCharacter::SetCanAttack(bool bCanAttack)
{
	if (BehaviorState != nullptr)
	{
		BehaviorState->bCanAttack = bCanAttack;
	}
}

FCharacterBehaviorState* AAscensionCharacter::GetBehaviorState()
{
	return BehaviorState;
}

bool AAscensionCharacter::IsAnimMontageFinished()
{
	return GetMesh()->GetAnimInstance()->Montage_GetIsStopped(GetCurrentMontage());
}

bool AAscensionCharacter::IsAnimMontagePlaying()
{
	return GetMesh()->GetAnimInstance()->Montage_IsPlaying(GetCurrentMontage());
}

