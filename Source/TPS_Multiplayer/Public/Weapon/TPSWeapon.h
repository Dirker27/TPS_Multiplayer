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
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Configuration")
    TObjectPtr<UTPSWeaponConfiguration> Configuration;
    //
    //- Muzzle/LaunchPoint
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Configuration")
    FTransform Muzzle = GetTransform();

    //- State --------------------------------------------=
	//
    //- Ammo
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|State", Replicated);
    int CurrentAmmunition;
    //
    //- IsAiming
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|State", Replicated)
    bool IsAiming;
    //
	//- IsFiring
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|State", Replicated)
    bool IsFiring;

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

//~ ============================================================= ~//
//  Equipable Overrides
//~ ============================================================= ~//
public:
	virtual void Equip();
    virtual void UnEquip();
};

