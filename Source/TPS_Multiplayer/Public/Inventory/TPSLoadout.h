// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"

#include "Weapon/TPSWeapon.h"

#include "TPSLoadout.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API UTPSLoadout : public UDataAsset
{
    GENERATED_BODY()

private:
    TObjectPtr<ATPSWeapon> primaryWeapon;
    TObjectPtr<ATPSWeapon> secondaryWeapon;
    TObjectPtr<ATPSWeapon> tertiaryWeapon;

    TObjectPtr<ATPSWeapon> lethalThrowable;
    TObjectPtr<ATPSWeapon> tacticalThrowable;

public:
    ATPSWeapon* GetWeaponFromEquipmentSlot(ETPSEquipmentSlot slot)
    {
        switch (slot)
        {
        case PrimaryWeapon:
            return primaryWeapon.Get();
        case SecondaryWeapon:
            return secondaryWeapon.Get();
        case TertiaryWeapon:
            return tertiaryWeapon.Get();
        case LethalThrowable:
            return lethalThrowable.Get();
        case TacticalThrowable:
            return tacticalThrowable.Get();
        default:
            return nullptr;
        }
    }
};