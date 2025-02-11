// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"
#include "Ammunition/TPSAmmunitionType.h"

#include "TPSWeaponConfiguration.generated.h"

UENUM(BlueprintType)
enum ETPSWeaponFireMode : int
{
    SingleShot = 0,
    FullAuto = 1,
    Burst = 2,
    Continuous = 3
};

UCLASS()
class TPS_MULTIPLAYER_API UTPSWeaponConfiguration : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TEnumAsByte<ETPSWeaponFireMode> FireMode = SingleShot;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "FireMode == ETPSWeaponFireMode::Burst", EditConditionHides))
    int BurstFireCount = 3;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float Damage = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float TriggerDelaySeconds = 0.1; // Delay before a fire actually happens (reaction/trigger-pull time)

    // Rounds / second
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float CycleRate = 3.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float ReloadDelaySeconds = 3.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int AmmunitionCapacity = 10;

    // Weapon can 'plus-1'
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    bool HasChamber = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TEnumAsByte<ETPSAmmunitionType> AmmunitionType;

    // Degrees of shot spread in MOA
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float AccuracySpreadMOA = 1.0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float RecoilScalar = 0.5; // 0 - 1 scale of recoil noise
};
