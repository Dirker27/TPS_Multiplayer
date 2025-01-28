// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"
#include "Ammunition/TPSAmmunitionType.h"
#include "Projectile/TPSProjectile.h"
#include "UObject/ObjectMacros.h"

#include "Weapon/TPSWeapon.h"

#include "TPSProjectileLauncher.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API ATPSProjectileLauncher : public ATPSWeapon
{
    GENERATED_BODY()

public:
    ATPSProjectileLauncher();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UTPSMountPoint> Muzzle;

public:
    //- Identity -----------------------------------------=
    //
    //- Name
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    TEnumAsByte<ETPSAmmunitionType> AmmunitionType;

    //- Configuration ------------------------------------=
    //
    //- Muzzle/LaunchPoint
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    //FTransform Muzzle = GetTransform();
    //
    //- Configuration
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    TSubclassOf<ATPSProjectile> ProjectileTemplate;

//~ ============================================================= ~//
//  BEHAVIOR
//~ ============================================================= ~//
public:

    UFUNCTION(BlueprintCallable)
    void Launch();

    //- Usable ------------------------------------------=
    //
    virtual void StartUse();
    //
    virtual void StopUse();
};