// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"

#include "Behavior/TPSMountPoint.h"

#include "TPSMountableActor.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API ATPSMountableActor : public AActor
{
    GENERATED_BODY()

protected:
    virtual void Tick(float DeltaSeconds) override
    {
        if (IsValid(MountPoint))
        {
            SetActorLocationAndRotation(
                MountPoint->GetCurrentPosition(),
                MountPoint->GetCurrentRotation()
            );
        }
    };

//~ ============================================================= ~//
//  ATTRIBUTES
//~ ============================================================= ~//
public:
    //- Configuration -----------------------------------=
    //
    //- Offset from Mount target
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
    FVector MountOffset = FVector::Zero();
    //
    //- Should Rotate?
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
    bool ShouldApplyRotation = true;
    //
    //- Use initial offsets on Mount?
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
    bool ShouldCaptureOffsetOnStart = true;

    //- State ---------------------------------------------=
    //
    //- Active(?) Mount Point
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
    TObjectPtr<UTPSMountPoint> MountPoint = nullptr;

//~ ============================================================= ~//
//  BEHAVIOR
//~ ============================================================= ~//
public:
    UFUNCTION(BlueprintCallable)
    void Mount (UTPSMountPoint* target)
    {
        UE_LOG(LogTemp, Log, TEXT("Mounted!"));
        MountPoint = target;
        OnMount();
    }
    UFUNCTION(BlueprintImplementableEvent)
    void OnMount();

    UFUNCTION(BlueprintCallable)
    void UnMount()
    {
        MountPoint = nullptr;
        OnUnMount();
    }
    UFUNCTION(BlueprintImplementableEvent)
    void OnUnMount();
};