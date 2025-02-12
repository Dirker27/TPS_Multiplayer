// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"

#include "Projectile/TPSProjectile.h"
#include "UObject/ObjectMacros.h"
#include "Weapon/TPSWeapon.h"

#include "TPSProjectileLauncher.generated.h"

UENUM(BlueprintType)
enum ETPSProjectileBehavior : int
{
    Slug = 0,
    Spread = 1
};

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
    //
    //- Projectile Behavior (Shotgun / Rifle)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    TEnumAsByte<ETPSProjectileBehavior> ProjectileBehavior;
    //
    //- Spread Count (iff Shotgun)
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Configuration", meta = (EditCondition = "ProjectileBehavior == ETPSProjectileBehavior::Spread", EditConditionHides))
    float SpreadCount = 1.0;

//~ ============================================================= ~//
//  BEHAVIOR
//~ ============================================================= ~//
public:
    UFUNCTION(BlueprintCallable)
    void LaunchProjectile(FRotator target);
    virtual void PerformFire(FRotator targetDirection) override; // Wired to ^

    //- Usable ------------------------------------------=
    //
    virtual void StartUse() override;
    //
    virtual void StopUse() override;
};