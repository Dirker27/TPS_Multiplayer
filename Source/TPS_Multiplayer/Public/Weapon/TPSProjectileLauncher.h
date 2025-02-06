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

public:
    //- Configuration ------------------------------------=
    //
    //- Muzzle/LaunchPoint
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    TObjectPtr<UTPSMountPoint> Muzzle;
    //
    //- Fired Projectile
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    TSubclassOf<ATPSProjectile> ProjectileTemplate;

//~ ============================================================= ~//
//  BEHAVIOR
//~ ============================================================= ~//
public:
    UFUNCTION(BlueprintCallable)
    void LaunchProjectile();
    virtual void PerformFire() override; // Wired to ^

    //- Usable ------------------------------------------=
    //
    virtual void StartUse() override;
    //
    virtual void StopUse() override;
};