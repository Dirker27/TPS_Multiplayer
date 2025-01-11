// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"

#include "Inventory/TPSEquipmentSlot.h"
#include "Weapon/TPSWeapon.h"

#include "TPSLoadout.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API UTPSLoadout : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ATPSEquipableItem> primaryWeapon;
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ATPSEquipableItem> secondaryWeapon;
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ATPSEquipableItem> tertiaryWeapon;
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ATPSEquipableItem> lethalEquipment;
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ATPSEquipableItem> tacticalEquipment;

public:
    TObjectPtr<ATPSEquipableItem> PrimaryWeaponInstance;
    TObjectPtr<ATPSEquipableItem> SecondaryWeaponInstance;
    TObjectPtr<ATPSEquipableItem> TertiaryWeaponInstance;

    TObjectPtr<ATPSEquipableItem> LethalEquipmentInstance;
    TObjectPtr<ATPSEquipableItem> TacticalEquipmentInstance;

public:
    ATPSEquipableItem* GetItemFromEquipmentSlot(ETPSEquipmentSlot slot)
    {
        switch (slot)
        {
        case ETPSEquipmentSlot::PrimaryWeapon:
            return PrimaryWeaponInstance;
        case ETPSEquipmentSlot::SecondaryWeapon:
            return SecondaryWeaponInstance;
        case ETPSEquipmentSlot::TertiaryWeapon:
            return TertiaryWeaponInstance;
        case ETPSEquipmentSlot::LethalEquipment:
            return LethalEquipmentInstance;
        case ETPSEquipmentSlot::TacticalEquipment:
            return TacticalEquipmentInstance;
        }
        return nullptr;
    }

    void BindItemToEquipmentSlot(ATPSEquipableItem* item, ETPSEquipmentSlot slot)
    {
        /*switch (slot)
        {
        case PrimaryWeapon:
            PrimaryWeaponInstance.;
        }*/
    }
};
