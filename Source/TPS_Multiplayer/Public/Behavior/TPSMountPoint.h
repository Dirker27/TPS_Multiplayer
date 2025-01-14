// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"

#include "TPSMountPoint.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API UTPSMountPoint : public USceneComponent
{
    GENERATED_BODY()

public:
    UTPSMountPoint();

#if WITH_EDITORONLY_DATA
/** Component shown in the editor only to indicate character facing */
    UPROPERTY()
    TObjectPtr<USphereComponent> SphereComponent;
#endif

//~ ============================================================= ~//
//  Configuration
//~ ============================================================= ~//
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MountPoint|Configuration")
    TWeakObjectPtr<USceneComponent> TargetParentComponent;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MountPoint|Configuration")
    FName TargetSocketName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MountPoint|Configuration")
    FVector OffsetPosition = FVector::Zero();
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MountPoint|Configuration")
    FVector OffsetEulerRotation = FVector::Zero();

//~ ============================================================= ~//
//  BEHAVIOR
//~ ============================================================= ~//
public:
    UFUNCTION(BlueprintCallable)
    FVector GetCurrentPosition() const;
    UFUNCTION(BlueprintCallable)
    FVector GetCurrentEulerRotation() const;
};