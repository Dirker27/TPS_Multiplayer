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
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


//~ ============================================================= ~//
//  STATE
//~ ============================================================= ~//
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EquipmentManager|State", Replicated)
    TEnumAsByte<ETPSEquipmentSlot> ActiveEquipmentSlot;

    //WeaponController weaponController;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentManager|State")
    TObjectPtr<UTPSLoadout> Loadout;

//~ ============================================================= ~//
//  CONFIGURATION
//~ ============================================================= ~//
public:
    //- Equipment Slot Bones ------------------------------=
    //
    //- Parent Mesh
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EquipmentManager|Configuration")
    TWeakObjectPtr<USkeletalMeshComponent> TargetMesh;
    //
    //- Weapon Hands
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EquipmentManager|Configuration")
    FName PrimaryWeaponHandBone;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EquipmentManager|Configuration")
    FName SecondaryWeaponHandBone;
    //
    //- Hip Holsters
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EquipmentManager|Configuration")
    FName LeftHipHolsterBone;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EquipmentManager|Configuration")
    FName RightHipHolsterBone;
    //
    //- Leg Holsters
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EquipmentManager|Configuration")
    FName LeftLegHolsterBone;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EquipmentManager|Configuration")
    FName RightLegHolsterBone;
    //
    //- Back Holsters
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EquipmentManager|Configuration")
    FName BackHolsterBone;

//~ ============================================================= ~//
//  COMPONENTS
//~ ============================================================= ~//
private:
    //- Equipment Slot Mounts ------------------------------=
    //
    //- Weapon Hands
    TObjectPtr<UTPSMountPoint> PrimaryWeaponHand;
    TObjectPtr<UTPSMountPoint> SecondaryWeaponHand;
    //
    //- Hip Holsters
    TObjectPtr<UTPSMountPoint> LeftHipHolster;
    TObjectPtr<UTPSMountPoint> RightHipHolster;
    //
    //- Leg Holsters
    TObjectPtr<UTPSMountPoint> LeftLegHolster;
    TObjectPtr<UTPSMountPoint> RightLegHolster;
    //
    //- Back Holsters
    TObjectPtr<UTPSMountPoint> BackHolster;

//~ ============================================================= ~//
//  PUBLIC OPERATIONS
//~ ============================================================= ~//
public:
    //UFUNCTION(BlueprintCallable)
    void BindToMesh(USkeletalMeshComponent* mesh);

    UFUNCTION(BlueprintCallable)
    void Initialize();
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
    void UnEquipActive();
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
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category="EquipmentManager|State")
    TObjectPtr<ATPSEquipableItem> PrimaryWeaponInstance;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "EquipmentManager|State")
    TObjectPtr<ATPSEquipableItem> SecondaryWeaponInstance;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "EquipmentManager|State")
    TObjectPtr<ATPSEquipableItem> TertiaryWeaponInstance;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "EquipmentManager|State")
    TObjectPtr<ATPSEquipableItem> LethalEquipmentInstance;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "EquipmentManager|State")
    TObjectPtr<ATPSEquipableItem> TacticalEquipmentInstance;

public:
    UFUNCTION(BlueprintCallable)
    ATPSEquipableItem* GetItemFromEquipmentSlot(ETPSEquipmentSlot slot) const;
    UTPSMountPoint* GetMountPointForSlot(ETPSEquipmentSlot slot) const;
};