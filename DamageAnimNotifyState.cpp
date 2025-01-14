// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageAnimNotifyState.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CollisionQueryParams.h"
#include "Kismet/GameplayStatics.h"
#include "CombatInterface.h"
#include "Weapon.h"

void UDamageAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    if (MeshComp != nullptr)
    {
        if (!bIsHit)
        {
            FHitResult HitResult;

            auto* const Owner = MeshComp->GetOwner();
            FCollisionQueryParams CollisionParams;
            CollisionParams.AddIgnoredActor(Owner);

            TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
            ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

            FVector Start = MeshComp->GetSocketLocation(TEXT("weapon_start"));
            FVector End = MeshComp->GetSocketLocation(TEXT("weapon_end"));
            float Radius = 50.f;

            bIsHit = MeshComp->GetWorld()->SweepSingleByObjectType(
                HitResult,
                Start,
                End,
                FQuat::Identity,
                FCollisionObjectQueryParams(ObjectTypes),
                FCollisionShape::MakeSphere(Radius),
                CollisionParams
            );

            if (bIsHit)
            {
                if (HitResult.GetActor())
                {
                    UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitResult.GetActor()->GetName());
                    auto* const OwnerCombatInterface = Cast<ICombatInterface>(Owner);
                    if (OwnerCombatInterface != nullptr)
                    {
                        auto* const Weapon = OwnerCombatInterface->GetWeapon();
                        if (Weapon != nullptr)
                        {
                            UGameplayStatics::ApplyDamage(HitResult.GetActor(),
                                Weapon->GetStatus().ATK,
                                Owner->GetInstigatorController(),
                                Owner,
                                UDamageType::StaticClass());
                        }
                    }
                }
            }

            DrawDebugLine(MeshComp->GetWorld(), Start, End, FColor::Red, false, 3.0f);
        }
    }
}

void UDamageAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    bIsHit = false;
}