// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"

#include "Inventory/TPSEquipableItem.h"
#include "Weapon/TPSWeaponType.h"

#include "TPSWeapon.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API ATPSWeapon : public ATPSEquipableItem
{
    GENERATED_BODY()

public:
    //ATPSWeapon();
    //~ATPSWeapon();

//~ ============================================================= ~//
//  ATTRIBUTES
//~ ============================================================= ~//
public:
    //- Identity ------------------------------------------=
    //
    //- Type
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Identity")
    TEnumAsByte<ETPSWeaponType> Type;

//~ ============================================================= ~//
//  Blueprint Extensions
//~ ============================================================= ~//
public:
    //- Transforms -------------------------------------------=
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

