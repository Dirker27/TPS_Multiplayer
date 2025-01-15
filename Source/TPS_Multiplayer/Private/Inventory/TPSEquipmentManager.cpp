// (C) ToasterCat Studios 2025

#include "Inventory/TPSEquipmentManager.h"

#include "Behavior/TPSMountPoint.h"

UTPSEquipmentManager::UTPSEquipmentManager()
{
    Loadout = CreateDefaultSubobject<UTPSLoadout>(TEXT("CustomLoadout"));

    PrimaryWeaponHand = CreateDefaultSubobject<UTPSMountPoint>(TEXT("MP-PrimaryWeaponHand"));
    SecondaryWeaponHand = CreateDefaultSubobject<UTPSMountPoint>(TEXT("MP-SecondaryWeaponHand"));

    BackHolster = CreateDefaultSubobject<UTPSMountPoint>(TEXT("MP-BackHolster"));
    LeftHipHolster = CreateDefaultSubobject<UTPSMountPoint>(TEXT("MP-LeftHipHolster"));
    LeftLegHolster = CreateDefaultSubobject<UTPSMountPoint>(TEXT("MP-LeftLegHolster"));
    RightHipHolster = CreateDefaultSubobject<UTPSMountPoint>(TEXT("MP-RightHipHolster"));
    RightLegHolster = CreateDefaultSubobject<UTPSMountPoint>(TEXT("MP-RightLegHolster"));
}

void UTPSEquipmentManager::BeginPlay()
{
    //BindToMesh(TargetMesh);

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

    PrimaryWeaponHand->TargetParentComponent = TargetMesh;
    SecondaryWeaponHand->TargetParentComponent = TargetMesh;
    BackHolster->TargetParentComponent = TargetMesh;
    LeftHipHolster->TargetParentComponent = TargetMesh;
    LeftLegHolster->TargetParentComponent = TargetMesh;
    RightHipHolster->TargetParentComponent = TargetMesh;
    RightLegHolster->TargetParentComponent = TargetMesh;

    PrimaryWeaponHand->TargetSocketName = FName(TEXT("hand_r"));
    SecondaryWeaponHand->TargetSocketName = FName(TEXT("hand_l"));
    BackHolster->TargetSocketName = FName(TEXT("spine_05"));
    LeftHipHolster->TargetSocketName = FName(TEXT("thigh_l"));
    LeftLegHolster->TargetSocketName = FName(TEXT("calf_l"));
    RightHipHolster->TargetSocketName = FName(TEXT("thigh_r"));
    RightLegHolster->TargetSocketName = FName(TEXT("calf_r"));

    /*if (IsValid(TargetMesh)) {
        UE_LOG(LogTemp, Log, TEXT("Mounting Holsters..."));

        if (IsValid(PrimaryWeaponHand) && !PrimaryWeaponHandBone.IsNone())
        {
            PrimaryWeaponHand->SetupAttachment(TargetMesh, PrimaryWeaponHandBone);;
        }
        if (IsValid(SecondaryWeaponHand) && !SecondaryWeaponHandBone.IsNone())
        {
            SecondaryWeaponHand->SetupAttachment(TargetMesh, SecondaryWeaponHandBone);
        }

        if (IsValid(BackHolster) && !BackHolsterBone.IsNone())
        {
            BackHolster->SetupAttachment(TargetMesh, BackHolsterBone);
        }
        if (IsValid(LeftHipHolster) && !LeftHipHolsterBone.IsNone())
        {
            LeftHipHolster->SetupAttachment(TargetMesh, LeftHipHolsterBone);
        }
        if (IsValid(LeftLegHolster) && !LeftLegHolsterBone.IsNone())
        {
            LeftLegHolster->SetupAttachment(TargetMesh, LeftLegHolsterBone);
        }
        if (IsValid(RightHipHolster) && !RightHipHolsterBone.IsNone())
        {
            RightHipHolster->SetupAttachment(TargetMesh, RightHipHolsterBone);
        }
        if (IsValid(RightLegHolster) && !RightLegHolsterBone.IsNone())
        {
            RightLegHolster->SetupAttachment(TargetMesh, RightLegHolsterBone);
        }
    }*/
}


//~ ============================================================= ~//
//  EQUIPMENT OPERATIONS
//~ ============================================================= ~//

void UTPSEquipmentManager::EquipWeaponToHolster(ATPSEquipableItem* weapon, ETPSEquipmentSlot slot)
{
    if (!IsValid(weapon)) { return; }

    UTPSMountPoint* mount = GetMountPointForSlot(slot);
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
    UnEquipActive();
    EquipAndArm(ETPSEquipmentSlot::PrimaryWeapon);
}
void UTPSEquipmentManager::EquipSecondary()
{
    UnEquipActive();
    EquipAndArm(ETPSEquipmentSlot::SecondaryWeapon);
}
void UTPSEquipmentManager::EquipTertiary() {
    UnEquipActive();
    EquipAndArm(ETPSEquipmentSlot::TertiaryWeapon);
}
void UTPSEquipmentManager::EquipLethalThrowable() {
    UnEquipActive();
    EquipAndArm(ETPSEquipmentSlot::LethalEquipment);
}
void UTPSEquipmentManager::EquipTacticalThrowable() {
    UnEquipActive();
    EquipAndArm(ETPSEquipmentSlot::TacticalEquipment);
}

void UTPSEquipmentManager::WeaponSwap() {
    UE_LOG(LogTemp, Log, TEXT("Swapping Weapons..."));

    // Needs to acct for non-populated slots.

    /*int nextSlot = ((int)ActiveEquipmentSlot) + 1 % 5;

    UnEquipActive();
    EquipAndArm((ETPSEquipmentSlot) nextSlot);*/
}

void UTPSEquipmentManager::EquipmentSwap() {
    UE_LOG(LogTemp, Log, TEXT("Swapping Equipment..."));
}

void UTPSEquipmentManager::InstantiateLoadout()
{
    if (!IsValid(Loadout)) { return; }

    if (IsValid(Loadout->primaryWeapon)) {
        UE_LOG(LogTemp, Log, TEXT("Instantiating Primary Weapon [%s]..."), *Loadout->primaryWeapon->GetName());
        PrimaryWeaponInstance = GetWorld()->SpawnActor<ATPSEquipableItem>(Loadout->primaryWeapon);
        //PrimaryWeaponInstance->SetReplicates(true);
        //PrimaryWeaponInstance->SetReplicateMovement(true);
    }
    if (IsValid(Loadout->secondaryWeapon)) {
        UE_LOG(LogTemp, Log, TEXT("Instantiating Secondary Weapon [%s]..."), *Loadout->secondaryWeapon->GetName());
        SecondaryWeaponInstance = GetWorld()->SpawnActor<ATPSEquipableItem>(Loadout->secondaryWeapon);
    }
    if (IsValid(Loadout->tertiaryWeapon)) {
        UE_LOG(LogTemp, Log, TEXT("Instantiating Tertiary Weapon [%s]..."), *Loadout->tertiaryWeapon->GetName());
        TertiaryWeaponInstance = GetWorld()->SpawnActor<ATPSEquipableItem>(Loadout->tertiaryWeapon);
    }
    if (IsValid(Loadout->tacticalEquipment)) {
        UE_LOG(LogTemp, Log, TEXT("Instantiating Tactical Equipment [%s]..."), *Loadout->tacticalEquipment->GetName());
        TacticalEquipmentInstance = GetWorld()->SpawnActor<ATPSEquipableItem>(Loadout->tacticalEquipment);
    }
    if (IsValid(Loadout->lethalEquipment)) {
        UE_LOG(LogTemp, Log, TEXT("Instantiating Lethal Equipment [%s]..."), *Loadout->lethalEquipment->GetName());
        LethalEquipmentInstance = GetWorld()->SpawnActor<ATPSEquipableItem>(Loadout->lethalEquipment);
    }
}

void UTPSEquipmentManager::UnEquipActive() {
    if (ActiveEquipmentSlot == ETPSEquipmentSlot::None) { return; }

    ATPSEquipableItem* weapon = GetItemInstanceFromEquipmentSlot(ActiveEquipmentSlot);
    EquipWeaponToHolster(weapon, ActiveEquipmentSlot);

    //weaponController.activeWeapons.Clear();
    ActiveEquipmentSlot = ETPSEquipmentSlot::None;
}

void UTPSEquipmentManager::EquipAndArm(ETPSEquipmentSlot equipmentSlot) {
    ATPSEquipableItem* item = GetItemInstanceFromEquipmentSlot(equipmentSlot);

    if (item) {
        EquipToPrimaryWeaponHand(item);
        //weaponController.activeWeapons.Add(weapon);
        ActiveEquipmentSlot = equipmentSlot;

        item->Equip();
    }
}


ATPSEquipableItem* UTPSEquipmentManager::GetItemInstanceFromEquipmentSlot(ETPSEquipmentSlot slot)
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

UTPSMountPoint* UTPSEquipmentManager::GetMountPointForSlot(ETPSEquipmentSlot slot)
{
    UTPSMountPoint* mount = nullptr;
    switch (slot)
    {
    case PrimaryWeapon:
        mount = RightLegHolster;
        break;
    case SecondaryWeapon:
        mount = RightHipHolster;
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
    return mount;
}