// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"

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
    UPROPERTY(EditDefaultsOnly)
    TEnumAsByte<ETPSWeaponFireMode> FireMode = SingleShot;

    UPROPERTY(EditDefaultsOnly)
    float Damage = 1;

    UPROPERTY(EditDefaultsOnly)
    float FireDelaySeconds = 0.01; // Delay before a fire actually happens (reaction/trigger-pull time)

    UPROPERTY(EditDefaultsOnly)
    float FireRateDelaySeconds = 0.2;

    UPROPERTY(EditDefaultsOnly)
    float ReloadDelaySeconds = 2;

    UPROPERTY(EditDefaultsOnly)
    int AmmunitionCapacity = 10;

    UPROPERTY(EditDefaultsOnly)
    float AccuracyScalar = 0.5; // 0 - 1 scale of noise
};
