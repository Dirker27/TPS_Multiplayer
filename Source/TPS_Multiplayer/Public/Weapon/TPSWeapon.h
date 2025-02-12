// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"

#include "Inventory/TPSEquipableItem.h"
#include "Reticle/TPSReticle.h"
#include "Weapon/TPSWeaponType.h"
#include "Weapon/TPSWeaponConfiguration.h"
#include "Weapon/TPSWeaponState.h"

#include "TPSWeapon.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API ATPSWeapon : public ATPSEquipableItem
{
    GENERATED_BODY()

public:
    ATPSWeapon();
    //~ATPSWeapon();

    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

//~ ============================================================= ~//
//  ATTRIBUTES
//~ ============================================================= ~//
public:
    //- Identity -----------------------------------------=
    //
    //- Type
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Identity")
    TEnumAsByte<ETPSWeaponType> Type;

    //- Configuration ------------------------------------=
    //
    //- Configuration
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TObjectPtr<UTPSWeaponConfiguration> Configuration;
    //
    //- UI Reticle
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    TObjectPtr<UTPSWeaponReticle> Reticle;

    //- State --------------------------------------------=
	//
    //- Ammo
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", Replicated);
    int CurrentAmmunitionCount;
    //
    //- State
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", Replicated)
    TEnumAsByte<ETPSWeaponState> CurrentWeaponState;
    //
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State", Replicated)
    TEnumAsByte<ETPSWeaponState> PreviousWeaponState;
    //
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", Replicated)
    bool IsReloading;
    //
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", Replicated)
    bool IsFiring;
    //
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    bool HasEverFired;
    //
    //- IsAiming (Behavior / Aesthetic Modifier)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", Replicated)
    bool IsAiming;
    //
    //- Fire Control -----
    //
    //- Targeting
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State");
    FRotator TargetDirection;
    //
    //- Meter fire rate
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    float TimeLastFired;
    //
    //- Consume the trigger (single/burst mode)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    bool HasTriggerCompleted;
    //
    //- For burst-fire count
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    int SuccessiveFireCount;

//~ ============================================================= ~//
//  BEHAVIOR
//~ ============================================================= ~//
public:
    UFUNCTION(BlueprintCallable)
    void Fire();
    UFUNCTION(BlueprintImplementableEvent)
    void OnFire();

    virtual void PerformFire(FRotator targetDirection) { UE_LOG(LogTemp, Log, TEXT("Weapon::PerformFire()")); };

    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool CanFire();

    UFUNCTION(BlueprintCallable)
    void StartReload();

    UFUNCTION(BlueprintCallable)
    void CommitReload(int newAmmunitionCount);

private:
    UFUNCTION(BlueprintCallable)
    void ApplyWeaponState(ETPSWeaponState newState);

//~ ============================================================= ~//
//  Equipable Overrides
//~ ============================================================= ~//
public:
    virtual void StartUse() override;
    virtual void StopUse() override;
	virtual void Equip() override;
    virtual void UnEquip() override;

//~ ============================================================= ~//
//  Blueprint Extensions
//~ ============================================================= ~//
public:
    //- Transforms -----------------------------------------=
    //
    //- WeaponType
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FString WeaponTypeToFString(const ETPSWeaponType t) {
        return FString(ETPSWeaponTypeToString(t));
    };
    //
    //- WeaponState
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FString WeaponStateToFString(ETPSWeaponState state) {
        return FString(ETPSWeaponStateToString(state));
    };
};

