// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"

#include "Weapon/TPSWeapon.h"

#include "TPSEquippableInventory.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API ATPSEquippableInventory : public AActor
{
    GENERATED_BODY()

public:
    ATPSEquippableInventory();
    ~ATPSEquippableInventory();

//~ ============================================================= ~//
//  ATTRIBUTES
//~ ============================================================= ~//
public:

    //- Equipment Slot Bones ------------------------------=
    //
    //- Weapon Hands
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName PrimaryWeaponHandBone;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SecondaryWeaponHandBone;
    //
    //- Hip Holsters
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName LeftHipHolster;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName RightHipHolster;
    //
    //- Leg Holsters
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName LeftLegHolster;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName RightLegHolster;
    //
    //- Back Holsters
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName BackHolster;

//~ ============================================================= ~//
//  ATTRIBUTES
//~ ============================================================= ~//
public:

    void EquipToPrimaryWeaponHand(ATPSWeapon* weapon);
    void EquipToSecondaryWeaponHand(ATPSWeapon* weapon);

    void EquipToPrimaryHolster(ATPSWeapon* weapon);
    void EquipToSecondaryHolster(ATPSWeapon* weapon);

    void EquipToTacticalHolster(ATPSWeapon* weapon);
    void EquipToLethalHolster(ATPSWeapon* weapon);

    void EquipToBackHolster(ATPSWeapon* weapon);
};