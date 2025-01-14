// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "AscensionCharacter.h"
#include "CombatInterface.h"
#include "AscenderAnimMontages.h"

#include "Ascender.generated.h"


UCLASS()
class ASCENSION_API AAscender : public AAscensionCharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAscender();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	bool IsSheath();

	UFUNCTION(BlueprintCallable)
	void Equip(class AWeapon* Weapon, FName SocketName);

	UFUNCTION(BlueprintCallable)
	void DisableCharacterInput(float Delay);

	UFUNCTION(BlueprintCallable)
	bool GetIsRolling();

	UFUNCTION(BlueprintCallable)
	class UCombatComponent* GetCombatComponent();

private:

	void InitializeInputActionAndContext();
	void InitializeComponents();
	void SetupComponentsAttachment();
	void SetupStimulusSource();

	void OnMoveForwardPressed(const FInputActionInstance& Instance);
	void OnMoveRightPressed(const FInputActionInstance& Instance);
	void LookUp(const FInputActionInstance& Instance);
	void Turn(const FInputActionInstance& Instance);
	void OnRollPressed();
	void OnSheathPressed();
	void OnDashPressed();
	void OnDashReleased();

	template<typename T>
	T* FindObjectByPath(const TCHAR* Path);
	void AddDefaultInputMappingContext();
	void BindInputActionToComponent(class UInputComponent* PlayerInputComponent);
	class UEnhancedInputLocalPlayerSubsystem* GetInputLocalPlayerSubsystem();

	//void RenerateStamina();
	void ClampLookUpAngle();
	void RotateWhileRolling(float DeltaTime);
	void CalculateRollTargetDirection();
	void UpdateHealthWidget();
	void UpdateStaminaWidget();

	void MeleeAttack_Implementation() override;
	void DashAttack_Implementation() override;
	void OnDeath() override;

	class AWeapon* GetWeapon() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UCombatComponent* CombatSystem;

	class UAscensionPlayerHUD* StatusWidget;

	class UAIPerceptionStimuliSourceComponent* StimulusSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input",
		meta = (AllowPrivateAccess = "true", ClampMin = "0.0", ClampMax = "90.0"))
	float MaxCameraPitch = 50.f;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* DefaultInputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* InputActionMoveForward;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InputActionMoveRight;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InputActionLookUp;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InputActionTurn;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InputActionDash;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InputActionRoll;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InputActionSheath;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InputActionAttack;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InputActionDashAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement",
		meta = (AllowPrivateAccess = "true", ClampMin = "0.0", ClampMax = "1.0"))
	float SpringArmRotationSpeedMultiplier = 0.2f;

	UPROPERTY(EditAnywhere, Category = "Equipment")
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AWeapon* EquippedWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages", meta = (AllowPrivateAccess = "true"))
	FAscenderAnimMontages AscenderAnimMontages;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector RollTargetDirection;
};

template<typename T>
inline T* AAscender::FindObjectByPath(const TCHAR* Path)
{
	ConstructorHelpers::FObjectFinder<T> ObjectSearchResult(Path);

	return ObjectSearchResult.Succeeded() ? ObjectSearchResult.Object : nullptr;
}
