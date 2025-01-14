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
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EquipmentManager.State")
    TEnumAsByte<ETPSEquipmentSlot> ActiveEquipmentSlot;

    //WeaponController weaponController;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentManager.State")
    TObjectPtr<UTPSLoadout> Loadout;

//~ ============================================================= ~//
//  CONFIGURATION
//~ ============================================================= ~//
public:
    //- Equipment Slot Bones ------------------------------=
    //
    //- Parent Mesh
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EquipmentManager.Configuration")
    TObjectPtr<USkeletalMeshComponent> TargetMesh;
    //- Weapon Hands
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EquipmentManager.Configuration")
    FName PrimaryWeaponHandBone;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EquipmentManager.Configuration")
    FName SecondaryWeaponHandBone;
    //
    //- Hip Holsters
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EquipmentManager.Configuration")
    FName LeftHipHolsterBone;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EquipmentManager.Configuration")
    FName RightHipHolsterBone;
    //
    //- Leg Holsters
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EquipmentManager.Configuration")
    FName LeftLegHolsterBone;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EquipmentManager.Configuration")
    FName RightLegHolsterBone;
    //
    //- Back Holsters
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EquipmentManager.Configuration")
    FName BackHolsterBone;

//~ ============================================================= ~//
//  COMPONENTS
//~ ============================================================= ~//
protected:
    //- Equipment Slot Mounts ------------------------------=
    //
    //- Weapon Hands
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EquipmentManager.Components")
    TObjectPtr<UTPSMountPoint> PrimaryWeaponHand;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EquipmentManager.Components")
    TObjectPtr<UTPSMountPoint> SecondaryWeaponHand;
    //
    //- Hip Holsters
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EquipmentManager.Components")
    TObjectPtr<UTPSMountPoint> LeftHipHolster;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EquipmentManager.Components")
    TObjectPtr<UTPSMountPoint> RightHipHolster;
    //
    //- Leg Holsters
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EquipmentManager.Components")
    TObjectPtr<UTPSMountPoint> LeftLegHolster;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EquipmentManager.Components")
    TObjectPtr<UTPSMountPoint> RightLegHolster;
    //
    //- Back Holsters
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EquipmentManager.Components")
    TObjectPtr<UTPSMountPoint> BackHolster;

//~ ============================================================= ~//
//  PUBLIC OPERATIONS
//~ ============================================================= ~//
public:
    //UFUNCTION(BlueprintCallable)
    void BindToMesh(USkeletalMeshComponent* mesh);

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
    void EquipWeaponToHolster(ATPSEquipableItem* weapon, ETPSEquipmentSlot slot);
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


protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="EquipmentManager.State")
    TObjectPtr<ATPSEquipableItem> PrimaryWeaponInstance;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EquipmentManager.State")
    TObjectPtr<ATPSEquipableItem> SecondaryWeaponInstance;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EquipmentManager.State")
    TObjectPtr<ATPSEquipableItem> TertiaryWeaponInstance;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EquipmentManager.State")
    TObjectPtr<ATPSEquipableItem> LethalEquipmentInstance;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EquipmentManager.State")
    TObjectPtr<ATPSEquipableItem> TacticalEquipmentInstance;

private:
    ATPSEquipableItem* GetItemInstanceFromEquipmentSlot(ETPSEquipmentSlot slot)
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
};