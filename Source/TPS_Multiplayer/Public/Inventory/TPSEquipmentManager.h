// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"

#include "Inventory/TPSEquipmentSlot.h"
#include "Inventory/TPSLoadout.h"
#include "Weapon/TPSWeapon.h"

#include "TPSEquipmentManager.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API UTPSEquipmentManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UTPSEquipmentManager();
    //~UTPSEquipmentManager();

protected:
    virtual void BeginPlay() override;

//~ ============================================================= ~//
//  STATE
//~ ============================================================= ~//
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TEnumAsByte<ETPSEquipmentSlot> ActiveEquipmentSlot;

    //WeaponController weaponController;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UTPSLoadout> Loadout;

//~ ============================================================= ~//
//  CONFIGURATION
//~ ============================================================= ~//
public:

    //- Equipment Slot Bones ------------------------------=
    //
    //- Weapon Hands
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    FName PrimaryWeaponHandBone;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    FName SecondaryWeaponHandBone;
    //
    //- Hip Holsters
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    FName LeftHipHolster;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    FName RightHipHolster;
    //
    //- Leg Holsters
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    FName LeftLegHolster;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    FName RightLegHolster;
    //
    //- Back Holsters
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    FName BackHolster;

//~ ============================================================= ~//
//  PUBLIC OPERATIONS
//~ ============================================================= ~//
public:
    UFUNCTION(BlueprintCallable)
    void InstantiateLoadout();

    UFUNCTION(BlueprintCallable)
    void Ready();
    UFUNCTION(BlueprintCallable)
    void UnReady();

    UFUNCTION(BlueprintCallable)
    void EquipPrimary();
    UFUNCTION(BlueprintCallable)
    void EquipSecondary();
    UFUNCTION(BlueprintCallable)
    void EquipTertiary();
    UFUNCTION(BlueprintCallable)
    void EquipLethalThrowable();
    UFUNCTION(BlueprintCallable)
    void EquipTacticalThrowable();

    UFUNCTION(BlueprintCallable)
    void WeaponSwap();
    UFUNCTION(BlueprintCallable)
    void EquipmentSwap();

//~ ============================================================= ~//
//  EQUIPMENT OPERATIONS
//~ ============================================================= ~//
protected:
    UFUNCTION(BlueprintCallable)
    void UnequipActive();
    UFUNCTION(BlueprintCallable)
    void EquipAndArm(ETPSEquipmentSlot equipmentSlot);

    UFUNCTION(BlueprintCallable)
    void EquipToPrimaryWeaponHand(ATPSEquipableItem* weapon);
    UFUNCTION(BlueprintCallable)
    void EquipToSecondaryWeaponHand(ATPSEquipableItem* weapon);
    UFUNCTION(BlueprintCallable)
    void EquipToPrimaryHolster(ATPSEquipableItem* weapon);
    UFUNCTION(BlueprintCallable)
	void EquipToSecondaryHolster(ATPSEquipableItem* weapon);
    UFUNCTION(BlueprintCallable)
    void EquipToTacticalHolster(ATPSEquipableItem* weapon);
    UFUNCTION(BlueprintCallable)
	void EquipToLethalHolster(ATPSEquipableItem* weapon);
    UFUNCTION(BlueprintCallable)
    void EquipToBackHolster(ATPSEquipableItem* weapon);

};