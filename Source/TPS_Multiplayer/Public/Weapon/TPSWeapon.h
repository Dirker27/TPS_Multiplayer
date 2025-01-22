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
    //- Muzzle/LaunchPoint
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    FTransform Muzzle = GetTransform();

    //- State --------------------------------------------=
	//
    //- Ammo
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", Replicated);
    int CurrentAmmunition;
    //
    //- IsAiming
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", Replicated)
    bool IsAiming;
    //
	//- IsFiring
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", Replicated)
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

