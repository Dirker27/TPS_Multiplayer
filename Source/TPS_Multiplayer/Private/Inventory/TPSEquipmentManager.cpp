// (C) ToasterCat Studios 2025

#include "Inventory/TPSEquipmentManager.h"

#include "ComponentUtils.h"
#include "GeometryCollection/GeometryCollectionAlgo.h"

UTPSEquipmentManager::UTPSEquipmentManager()
{
    //Loadout = CreateDefaultSubobject<UTPSLoadout>(TEXT("MyLoadout"));
    PrimaryWeaponHand = CreateDefaultSubobject<UTPSMountPoint>(TEXT("PrimaryWeaponHand"));
    SecondaryWeaponHand = CreateDefaultSubobject<UTPSMountPoint>(TEXT("SecondaryWeaponHand"));

    BackHolster = CreateDefaultSubobject<UTPSMountPoint>(TEXT("BackHolster"));
    LeftHipHolster = CreateDefaultSubobject<UTPSMountPoint>(TEXT("LeftHipHolster"));
    LeftLegHolster = CreateDefaultSubobject<UTPSMountPoint>(TEXT("LeftLegHolster"));
    RightHipHolster = CreateDefaultSubobject<UTPSMountPoint>(TEXT("RightHipHolster"));
    RightLegHolster = CreateDefaultSubobject<UTPSMountPoint>(TEXT("RightLegHolster"));
}

void UTPSEquipmentManager::BeginPlay()
{
    if (IsValid(Loadout)) {
        InstantiateLoadout();

        EquipToPrimaryHolster(GetItemInstanceFromEquipmentSlot(PrimaryWeapon));
        EquipToSecondaryHolster(GetItemInstanceFromEquipmentSlot(SecondaryWeapon));
        EquipToBackHolster(GetItemInstanceFromEquipmentSlot(TertiaryWeapon));

        EquipToLethalHolster(GetItemInstanceFromEquipmentSlot(LethalEquipment));
        EquipToTacticalHolster(GetItemInstanceFromEquipmentSlot(TacticalEquipment));
    }

    ActiveEquipmentSlot = ETPSEquipmentSlot::None;
}

void UTPSEquipmentManager::BindToMesh(USkeletalMeshComponent* mesh)
{
    TargetMesh = mesh;
    if (IsValid(TargetMesh)) {
        UE_LOG(LogTemp, Log, TEXT("Mounting Holsters..."));

        if (PrimaryWeaponHandBone.IsValid() && !PrimaryWeaponHandBone.IsNone())
        {
            PrimaryWeaponHand->SetupAttachment(TargetMesh, PrimaryWeaponHandBone);
        }
        if (SecondaryWeaponHandBone.IsValid() && !SecondaryWeaponHandBone.IsNone())
        {
            SecondaryWeaponHand->SetupAttachment(TargetMesh, SecondaryWeaponHandBone);
        }

        if (BackHolsterBone.IsValid() && !BackHolsterBone.IsNone())
        {
            BackHolster->SetupAttachment(TargetMesh, BackHolsterBone);
        }
        if (LeftHipHolsterBone.IsValid() && !LeftHipHolsterBone.IsNone())
        {
            LeftHipHolster->SetupAttachment(TargetMesh, LeftHipHolsterBone);
        }
        if (LeftLegHolsterBone.IsValid() && !LeftLegHolsterBone.IsNone())
        {
            LeftLegHolster->SetupAttachment(TargetMesh, LeftLegHolsterBone);
        }
        if (RightHipHolsterBone.IsValid() && !RightHipHolsterBone.IsNone())
        {
            RightHipHolster->SetupAttachment(TargetMesh, RightHipHolsterBone);
        }
        if (RightLegHolsterBone.IsValid() && !RightLegHolsterBone.IsNone())
        {
            RightLegHolster->SetupAttachment(TargetMesh, RightLegHolsterBone);
        }
    }
}


//~ ============================================================= ~//
//  EQUIPMENT OPERATIONS
//~ ============================================================= ~//

void UTPSEquipmentManager::EquipWeaponToHolster(ATPSEquipableItem* weapon, ETPSEquipmentSlot slot)
{
    if (!IsValid(weapon)) { return; }

    UTPSMountPoint* mount = nullptr;
    switch (slot)
    {
    case PrimaryWeapon:
        mount = PrimaryWeaponHand;
        break;
    case SecondaryWeapon:
        mount = SecondaryWeaponHand;
        break;
    case TertiaryWeapon:
        mount = BackHolster;
        break;
    case LethalEquipment:
        mount = LeftLegHolster;
        break;
    case TacticalEquipment:
        mount = LeftHipHolster;
        break;
    }
    if (!IsValid(mount)) { return; }

    weapon->Mount(mount);
}
void UTPSEquipmentManager::EquipToPrimaryWeaponHand(ATPSEquipableItem* weapon)
{
    if (!IsValid(weapon) || !IsValid(PrimaryWeaponHand)) { return; }

	weapon->Mount(PrimaryWeaponHand);
    UE_LOG(LogTemp, Log, TEXT("Weapon mounted to Primary Hand"));
}

void UTPSEquipmentManager::EquipToSecondaryWeaponHand(ATPSEquipableItem* weapon)
{
    if (!IsValid(weapon) || !IsValid(SecondaryWeaponHand)) { return; }

    weapon->Mount(SecondaryWeaponHand);
}

void UTPSEquipmentManager::EquipToPrimaryHolster(ATPSEquipableItem* weapon)
{
    EquipWeaponToHolster(weapon, PrimaryWeapon);
}
void UTPSEquipmentManager::EquipToSecondaryHolster(ATPSEquipableItem* weapon)
{
    EquipWeaponToHolster(weapon, SecondaryWeapon);
}
void UTPSEquipmentManager::EquipToTacticalHolster(ATPSEquipableItem* weapon)
{
    EquipWeaponToHolster(weapon, TacticalEquipment);
}
void UTPSEquipmentManager::EquipToLethalHolster(ATPSEquipableItem* weapon)
{
    EquipWeaponToHolster(weapon, LethalEquipment);
}
void UTPSEquipmentManager::EquipToBackHolster(ATPSEquipableItem* weapon)
{
    EquipWeaponToHolster(weapon, TertiaryWeapon);
}


//~ ============================================================= ~//
//  PUBLIC OPERATIONS
//~ ============================================================= ~//

void UTPSEquipmentManager::Ready()
{
    if (!IsValid(Loadout)) { return; }
    ActiveEquipmentSlot = ETPSEquipmentSlot::PrimaryWeapon;
    EquipToPrimaryWeaponHand(GetItemInstanceFromEquipmentSlot(PrimaryWeapon));

    /*weaponController.activeWeapons.Add(Loadout->primaryWeapon);
    weaponController.Ready();*/
}

void UTPSEquipmentManager::UnReady()
{
    if (!IsValid(Loadout)) { return; }
    /*weaponController.CancelReady();
    weaponController.activeWeapons.Clear();*/

    EquipToPrimaryHolster(GetItemInstanceFromEquipmentSlot(PrimaryWeapon));
    EquipToSecondaryHolster(GetItemInstanceFromEquipmentSlot(SecondaryWeapon));
    EquipToBackHolster(GetItemInstanceFromEquipmentSlot(TertiaryWeapon));

    EquipToLethalHolster(GetItemInstanceFromEquipmentSlot(LethalEquipment));
    EquipToTacticalHolster(GetItemInstanceFromEquipmentSlot(TacticalEquipment));
}

void UTPSEquipmentManager::EquipPrimary()
{
    UnequipActive();
    EquipAndArm(ETPSEquipmentSlot::PrimaryWeapon);
}
void UTPSEquipmentManager::EquipSecondary()
{
    UnequipActive();
    EquipAndArm(ETPSEquipmentSlot::SecondaryWeapon);
}
void UTPSEquipmentManager::EquipTertiary() {
    UnequipActive();
    EquipAndArm(ETPSEquipmentSlot::TertiaryWeapon);
}
void UTPSEquipmentManager::EquipLethalThrowable() {
    UnequipActive();
    EquipAndArm(ETPSEquipmentSlot::LethalEquipment);
}
void UTPSEquipmentManager::EquipTacticalThrowable() {
    UnequipActive();
    EquipAndArm(ETPSEquipmentSlot::TacticalEquipment);
}

void UTPSEquipmentManager::WeaponSwap() {
    UE_LOG(LogTemp, Log, TEXT("Swapping Weapons..."));

    // Needs to acct for non-populated slots.

    /*int nextSlot = ((int)ActiveEquipmentSlot) + 1 % 5;

    UnequipActive();
    EquipAndArm((ETPSEquipmentSlot) nextSlot);*/
}

void UTPSEquipmentManager::EquipmentSwap() {
    UE_LOG(LogTemp, Log, TEXT("Swapping Equipment..."));
}

void UTPSEquipmentManager::InstantiateLoadout()
{
    if (!IsValid(Loadout)) { return; }

    if (IsValid(Loadout->primaryWeapon)) {
        UE_LOG(LogTemp, Log, TEXT("Instantiating Primary Weapon []..."));
        PrimaryWeaponInstance = GetWorld()->SpawnActor<ATPSEquipableItem>(Loadout->primaryWeapon);
    }
    if (IsValid(Loadout->secondaryWeapon)) {
        UE_LOG(LogTemp, Log, TEXT("Instantiating Secondary Weapon []..."));
        SecondaryWeaponInstance = GetWorld()->SpawnActor<ATPSEquipableItem>(Loadout->secondaryWeapon);
    }
    if (IsValid(Loadout->tertiaryWeapon)) {
        UE_LOG(LogTemp, Log, TEXT("Instantiating Tertiary Weapon []..."));
        TertiaryWeaponInstance = GetWorld()->SpawnActor<ATPSEquipableItem>(Loadout->tertiaryWeapon);
    }
    if (IsValid(Loadout->tacticalEquipment)) {
        UE_LOG(LogTemp, Log, TEXT("Instantiating Tactical Equipment []..."));
        TacticalEquipmentInstance = GetWorld()->SpawnActor<ATPSEquipableItem>(Loadout->tacticalEquipment);
    }
    if (IsValid(Loadout->lethalEquipment)) {
        UE_LOG(LogTemp, Log, TEXT("Instantiating Lethal Equipment []..."));
        LethalEquipmentInstance = GetWorld()->SpawnActor<ATPSEquipableItem>(Loadout->lethalEquipment);
    }
}

void UTPSEquipmentManager::UnequipActive() {
    if (!IsValid(Loadout)) { return; }
    if (ActiveEquipmentSlot == ETPSEquipmentSlot::None) { return; }

    ATPSEquipableItem* weapon = GetItemInstanceFromEquipmentSlot(ActiveEquipmentSlot);
    EquipWeaponToHolster(weapon, ActiveEquipmentSlot);

    //weaponController.activeWeapons.Clear();
    ActiveEquipmentSlot = ETPSEquipmentSlot::None;
}

void UTPSEquipmentManager::EquipAndArm(ETPSEquipmentSlot equipmentSlot) {
    if (!IsValid(Loadout)) { return; }

    ATPSEquipableItem* item = GetItemInstanceFromEquipmentSlot(equipmentSlot);

    if (item) {
        EquipToPrimaryWeaponHand(item);
        //weaponController.activeWeapons.Add(weapon);
        ActiveEquipmentSlot = equipmentSlot;

        item->Equip();
    }
}