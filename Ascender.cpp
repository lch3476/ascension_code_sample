// Fill out your copyright notice in the Description page of Project Settings.


#include "Ascender.h"
#include "Camera/CameraComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"

#include "CombatComponent.h"
#include "AscensionGameplayStatics.h"
#include "CharacterBehaviorState.h"
#include "Weapon.h"
#include "CombatInterface.h"
#include "AscenderAnimMontages.h"
#include "AscensionPlayerHUD.h"

// Sets default values
AAscender::AAscender()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitializeComponents();
	SetupComponentsAttachment();
	InitializeInputActionAndContext();
	SetupStimulusSource();
}


// Called when the game starts or when spawned
void AAscender::BeginPlay()
{
	Super::BeginPlay();

	AddDefaultInputMappingContext();
	EquippedWeapon = Cast<AWeapon>(SpawnEquipment(WeaponClass, TEXT("weapon_sheath")));
	StatusWidget = Cast<UAscensionPlayerHUD>(HUD->GetWidget());
	UpdateHealthWidget();
}

void AAscender::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	
	Super::EndPlay(EndPlayReason);
}


// Called every frame
void AAscender::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ClampLookUpAngle();
	RotateWhileRolling(DeltaTime);
	
	UpdateStaminaWidget();
	CombatComponent->StaminaRegenerate(DeltaTime);
}

// Called to bind functionality to input
void AAscender::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	BindInputActionToComponent(PlayerInputComponent);
}

void AAscender::InitializeInputActionAndContext()
{
	DefaultInputMappingContext = FindObjectByPath<UInputMappingContext>(TEXT("/Game/Input/IMC_Default"));
	InputActionMoveForward = FindObjectByPath<UInputAction>(TEXT("/Game/Input/IA_MoveForward"));
	InputActionMoveRight = FindObjectByPath<UInputAction>(TEXT("/Game/Input/IA_MoveRight"));
	InputActionLookUp = FindObjectByPath<UInputAction>(TEXT("/Game/Input/IA_LookUp"));
	InputActionTurn = FindObjectByPath<UInputAction>(TEXT("/Game/Input/IA_Turn"));
	InputActionTurn = FindObjectByPath<UInputAction>(TEXT("/Game/Input/IA_Dash"));
	InputActionRoll = FindObjectByPath<UInputAction>(TEXT("/Game/Input/IA_Roll"));
	InputActionSheath = FindObjectByPath<UInputAction>(TEXT("/Game/Input/IA_Sheath"));
	InputActionAttack = FindObjectByPath<UInputAction>(TEXT("/Game/Input/IA_Attack"));
	InputActionDashAttack = FindObjectByPath<UInputAction>(TEXT("/Game/Input/IA_DashAttack"));
}

void AAscender::BindInputActionToComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent != nullptr)
	{
		EnhancedInputComponent->BindAction(InputActionMoveForward, ETriggerEvent::Triggered, this, &AAscender::OnMoveForwardPressed);
		EnhancedInputComponent->BindAction(InputActionMoveRight, ETriggerEvent::Triggered, this, &AAscender::OnMoveRightPressed);
		EnhancedInputComponent->BindAction(InputActionLookUp, ETriggerEvent::Triggered, this, &AAscender::LookUp);
		EnhancedInputComponent->BindAction(InputActionTurn, ETriggerEvent::Triggered, this, &AAscender::Turn);
		EnhancedInputComponent->BindAction(InputActionDash, ETriggerEvent::Triggered, this, &AAscender::OnDashPressed);
		EnhancedInputComponent->BindAction(InputActionDash, ETriggerEvent::Completed, this, &AAscender::OnDashReleased);
		EnhancedInputComponent->BindAction(InputActionRoll, ETriggerEvent::Triggered, this, &AAscender::OnRollPressed);
		EnhancedInputComponent->BindAction(InputActionSheath, ETriggerEvent::Triggered, this, &AAscender::OnSheathPressed);
		EnhancedInputComponent->BindAction(InputActionAttack, ETriggerEvent::Triggered, this, &AAscender::MeleeAttack_Implementation);
		EnhancedInputComponent->BindAction(InputActionDashAttack, ETriggerEvent::Triggered, this, &AAscender::DashAttack_Implementation);
	}
}

void AAscender::AddDefaultInputMappingContext()
{
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = GetInputLocalPlayerSubsystem();
	if (EnhancedInputLocalPlayerSubsystem != nullptr)
	{
		EnhancedInputLocalPlayerSubsystem->AddMappingContext(DefaultInputMappingContext, 0);
	}
}

void AAscender::InitializeComponents()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat Component"));
}


void AAscender::SetupComponentsAttachment()
{
	if (SpringArm != nullptr) SpringArm->SetupAttachment(RootComponent);
	if (Camera != nullptr) Camera->SetupAttachment(SpringArm);
}

void AAscender::SetupStimulusSource()
{
	if (StimulusSource != nullptr)
	{
		StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimulusSource->RegisterWithPerceptionSystem();
	}
}


UEnhancedInputLocalPlayerSubsystem* AAscender::GetInputLocalPlayerSubsystem()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	return PlayerController != nullptr ?
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()) : nullptr;
}

void AAscender::ClampLookUpAngle()
{
	APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
	PlayerCameraManager->ViewPitchMax = MaxCameraPitch;
	PlayerCameraManager->ViewPitchMin = -MaxCameraPitch;
}

void AAscender::RotateWhileRolling(float DeltaTime)
{
	if (BehaviorState->bIsRolling)
	{
		FRotator TargetRotation = FRotationMatrix::MakeFromX(RollTargetDirection).Rotator();

		FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 25.0f);
		SetActorRotation(NewRotation);
	}
}

void AAscender::CalculateRollTargetDirection()
{
	RollTargetDirection = GetVelocity().GetSafeNormal();

	if (RollTargetDirection.IsZero())
	{
		RollTargetDirection = GetActorForwardVector();
	}
}

void AAscender::UpdateHealthWidget()
{
	if (StatusWidget != nullptr && CombatComponent != nullptr)
	{
		StatusWidget->SetHealthPercent(CombatComponent->GetHealth() / CombatComponent->GetMaxHealth());
	}
}

void AAscender::UpdateStaminaWidget()
{
	if (StatusWidget != nullptr && CombatComponent != nullptr)
	{
		StatusWidget->SetStaminaPercent(CombatComponent->GetStamina() / CombatComponent->GetMaxStamina());
	}
}

void AAscender::MeleeAttack_Implementation()
{
	if (!IsSheath() 
		&& CanAttack() 
		&& !GetMovementComponent()->IsFalling()
		&& CombatComponent->HasEnoughStamina())
	{
		CombatComponent->DepleteStamina();
		CombatComponent->ComboAttack(AscenderAnimMontages.ComboAttackMontages);
	}
}


void AAscender::DashAttack_Implementation()
{
	if (!IsSheath()
		&& CanAttack()
		&& !GetMovementComponent()->IsFalling()
		&& CombatComponent->HasEnoughStamina())
	{
		CombatComponent->ResetCombo();
		CombatComponent->DepleteStamina();
		CombatComponent->Attack(AscenderAnimMontages.DashAttackMontage);
	}
}

void AAscender::OnDeath()
{
	GetCharacterMovement()->DisableMovement();
	StopAnimMontage();
	SetCanAttack(false);
	auto* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->bShowMouseCursor = false;
	}
}


AWeapon* AAscender::GetWeapon()
{
	return EquippedWeapon;
}


bool AAscender::IsSheath()
{
	if (BehaviorState != nullptr)
	{
		return BehaviorState->bIsSheath;
	}
	return false;
}

void AAscender::Equip(AWeapon* Weapon, FName SocketName)
{
	if (Weapon && GetMesh())
	{
		Weapon->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::SnapToTargetIncludingScale,
			SocketName);
	}
}


void AAscender::DisableCharacterInput(float Delay)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		DisableInput(PlayerController);
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(
			TimerHandle,
			[this, PlayerController]() { this->EnableInput(PlayerController); },
			Delay,
			false);
	}
}

bool AAscender::GetIsRolling()
{
	return BehaviorState->bIsRolling;
}

UCombatComponent* AAscender::GetCombatComponent()
{
	return CombatComponent;
}

void AAscender::OnMoveForwardPressed(const FInputActionInstance& Instance)
{
	if (!GetMovementComponent()->IsFalling()
		&& !IsAnimMontagePlaying())
	{
		FRotator ControlRotation = GetControlRotation();
		FVector ForwardVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::X);
		ForwardVector.Z = 0;
		ForwardVector.Normalize();

		FVector2D MovementVector = Instance.GetValue().Get<FVector2D>();

		AddMovementInput(ForwardVector, MovementVector.Y);
	}
}


void AAscender::OnMoveRightPressed(const FInputActionInstance& Instance)
{
	if (!GetMovementComponent()->IsFalling()
		&& !IsAnimMontagePlaying())
	{
		FRotator ControlRotation = GetControlRotation();
		FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);

		FVector2D MovementVector = Instance.GetValue().Get<FVector2D>();

		AddMovementInput(RightVector, MovementVector.X);
	}
}


void AAscender::LookUp(const FInputActionInstance& Instance)
{
	float InputValue = Instance.GetValue().Get<float>();

	AddControllerPitchInput(InputValue * SpringArmRotationSpeedMultiplier);
}


void AAscender::Turn(const FInputActionInstance& Instance)
{
	float InputValue = Instance.GetValue().Get<float>();
	AddControllerYawInput(InputValue * SpringArmRotationSpeedMultiplier);
}

void AAscender::OnRollPressed()
{
	if (BehaviorState != nullptr)
	{
		if (!IsAnimMontagePlaying() 
			&& !GetMovementComponent()->IsFalling()
			&& CombatComponent->HasEnoughStamina())
		{
			SetCanAttack(false);
			BehaviorState->bIsRolling = true;
			float Length;

			CalculateRollTargetDirection();
			CombatComponent->DepleteStamina();
			if (BehaviorState->bIsSheath)
			{
				Length = PlayAnimMontage(AscenderAnimMontages.RollForwardMontage);
			}
			else
			{
				Length = PlayAnimMontage(AscenderAnimMontages.CombatRollForwardMontage);
			}

			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, [this]() { BehaviorState->bIsRolling = false; }, Length - 0.3f, false);

		}
	}
}

void AAscender::OnSheathPressed()
{
	if (BehaviorState != nullptr 
		&& !GetMovementComponent()->IsFalling()
		&& !IsAnimMontagePlaying()
		&& GetCurrentSpeed() <= 0.0f)
	{
		if (BehaviorState->bIsSheath) 
		{
			if (AscenderAnimMontages.UnSheatheMontage != nullptr)
			{
				BehaviorState->bIsSheath = false;
				SetCanAttack(false);
				PlayAnimMontage(AscenderAnimMontages.UnSheatheMontage);
			}
		}
		else
		{
			if (AscenderAnimMontages.UnSheatheMontage != nullptr)
			{
				BehaviorState->bIsSheath = true;
				SetCanAttack(false);
				PlayAnimMontage(AscenderAnimMontages.SheatheMontage);
			}
		}
	}
}

void AAscender::OnDashPressed()
{
	GetCharacterMovement()->MaxWalkSpeed = 800.f;
}

void AAscender::OnDashReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}
