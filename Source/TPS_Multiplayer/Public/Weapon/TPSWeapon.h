// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"
#include "TPSWeaponConfiguration.h"

#include "Inventory/TPSEquipableItem.h"
#include "Weapon/TPSWeaponType.h"

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

    //- State --------------------------------------------=
	//
    //- Ammo
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", Replicated);
    int CurrentAmmunition;
    //
    //- IsReloading
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", Replicated)
    bool IsReloading;
    //
    //- IsAiming
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", Replicated)
    bool IsAiming;
    //
	//- IsFiring
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", Replicated)
    bool IsFiring;
    //
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    float TimeLastFired;
    //
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    bool HasEverFired;
    //
    //- If follow-up attacks are allowed per-press.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    bool CanFire;
    //
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    int SuccessiveFireCount;

//~ ============================================================= ~//
//  BEHAVIOR
//~ ============================================================= ~//
public:
    UFUNCTION(BlueprintCallable)
    void Fire();

    virtual void PerformFire() { UE_LOG(LogTemp, Log, TEXT("Weapon::PerformFire()")); };

    UFUNCTION(BlueprintCallable)
    void Reload();

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

};

