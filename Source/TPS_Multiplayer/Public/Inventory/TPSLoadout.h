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
};
