// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"

#include "Inventory/TPSEquipmentSlot.h"
#include "Inventory/TPSLoadout.h"
#include "Weapon/TPSWeapon.h"

#include "TPSEquipmentManager.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API ATPSEquipmentManager : public AActor
{
    GENERATED_BODY()

public:
    ATPSEquipmentManager();
    ~ATPSEquipmentManager();

protected:
    virtual void BeginPlay() override;

//~ ============================================================= ~//
//  STATE
//~ ============================================================= ~//
public:
    ETPSEquipmentSlot ActiveEquipmentSlot;

    //private WeaponController weaponController;
    UTPSLoadout Loadout;

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
    void EquipToPrimaryWeaponHand(ATPSWeapon* weapon);
    UFUNCTION(BlueprintCallable)
    void EquipToSecondaryWeaponHand(ATPSWeapon* weapon);
    UFUNCTION(BlueprintCallable)
    void EquipToPrimaryHolster(ATPSWeapon* weapon);
    UFUNCTION(BlueprintCallable)
	void EquipToSecondaryHolster(ATPSWeapon* weapon);
    UFUNCTION(BlueprintCallable)
    void EquipToTacticalHolster(ATPSWeapon* weapon);
    UFUNCTION(BlueprintCallable)
	void EquipToLethalHolster(ATPSWeapon* weapon);
    UFUNCTION(BlueprintCallable)
    void EquipToBackHolster(ATPSWeapon* weapon);

};