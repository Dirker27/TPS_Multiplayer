// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"

#include "TPSDestructible.generated.h"

/// Root behavior for Destructible Props.
///
/// Receives damage in raw Joules based on kinetic energy during collisions. 
UCLASS()
class TPS_MULTIPLAYER_API ATPSDestructible : public AActor
{
	GENERATED_BODY()

//~ ============================================================= ~//
//  ATTRIBUTES
//~ ============================================================= ~//
public:
    //- Configuration -----------------------------------=
    //
    //- Total Energy to Destruct
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float TotalDestructionEnergyJoules = 100.0f;
    //
    //- Minimum Energy req'd to Damage/Destruct
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float MinimumDestructionThresholdJoules = 1.0f;
    //
    //- Can take damage from world physics collisions
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
    bool IsPhysicsDamageEnabled = false;

    //- State ---------------------------------------------=
    //
    //- Lifetime Damage
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    float LifetimeEnergyAbsorbedJoules = 0;
    //
    //- Lifetime Damage
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    bool HasDestructed = false;

//~ ============================================================= ~//
//  BEHAVIOR
//~ ============================================================= ~//
public:
    UFUNCTION(BlueprintCallable)
    void ApplyEnergyJoules(float energy) { LifetimeEnergyAbsorbedJoules += energy; }

    UFUNCTION(BlueprintCallable)
    static float GetKineticEnergyJoules(UObject* object) { return 10.0f; }
};