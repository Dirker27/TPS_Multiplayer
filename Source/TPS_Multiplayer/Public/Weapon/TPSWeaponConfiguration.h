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

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int BurstFireCount = 3;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float Damage = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float FireDelaySeconds = 0.01; // Delay before a fire actually happens (reaction/trigger-pull time)

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float FireRateDelaySeconds = 0.2;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float ReloadDelaySeconds = 2;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int AmmunitionCapacity = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TEnumAsByte<ETPSAmmunitionType> AmmunitionType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float AccuracyScalar = 0.5; // 0 - 1 scale of accuracy noise

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float RecoilScalar = 0.5; // 0 - 1 scale of recoil noise
};
