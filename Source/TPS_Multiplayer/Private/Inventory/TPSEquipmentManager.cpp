// (C) ToasterCat Studios 2025

#include "Inventory/TPSEquipmentManager.h"

UTPSEquipmentManager::UTPSEquipmentManager()
{
    Loadout = CreateDefaultSubobject<UTPSLoadout>(TEXT("MyLoadout"));
}

void UTPSEquipmentManager::BeginPlay()
{
    InstantiateLoadout();

    EquipToPrimaryHolster(Loadout->GetItemFromEquipmentSlot(PrimaryWeapon));
    EquipToSecondaryHolster(Loadout->GetItemFromEquipmentSlot(SecondaryWeapon));
    EquipToBackHolster(Loadout->GetItemFromEquipmentSlot(TertiaryWeapon));

    EquipToLethalHolster(Loadout->GetItemFromEquipmentSlot(LethalEquipment));
    EquipToTacticalHolster(Loadout->GetItemFromEquipmentSlot(TacticalEquipment));

    ActiveEquipmentSlot = ETPSEquipmentSlot::None;
}

//~ ============================================================= ~//
//  EQUIPMENT OPERATIONS
//~ ============================================================= ~//

void UTPSEquipmentManager::EquipToPrimaryWeaponHand(ATPSEquipableItem* weapon)
{
	// Attach to parent bone
}

void UTPSEquipmentManager::EquipToSecondaryWeaponHand(ATPSEquipableItem* weapon)
{
	// Attach to parent bone
}

void UTPSEquipmentManager::EquipToPrimaryHolster(ATPSEquipableItem* weapon)
{
	// Attach to parent bone
}

void UTPSEquipmentManager::EquipToSecondaryHolster(ATPSEquipableItem* weapon)
{
	// Attach to parent bone
}

void UTPSEquipmentManager::EquipToTacticalHolster(ATPSEquipableItem* weapon)
{
	// Attach to parent bone
}

void UTPSEquipmentManager::EquipToLethalHolster(ATPSEquipableItem* weapon)
{
	// Attach to parent bone
}

void UTPSEquipmentManager::EquipToBackHolster(ATPSEquipableItem* weapon)
{
	// Attach to parent bone
}


//~ ============================================================= ~//
//  PUBLIC OPERATIONS
//~ ============================================================= ~//

void UTPSEquipmentManager::Ready()
{
    if (!IsValid(Loadout)) { return; }
    ActiveEquipmentSlot = ETPSEquipmentSlot::PrimaryWeapon;
    EquipToPrimaryWeaponHand(Loadout->GetItemFromEquipmentSlot(PrimaryWeapon));

    /*weaponController.activeWeapons.Add(Loadout->primaryWeapon);
    weaponController.Ready();*/
}

void UTPSEquipmentManager::UnReady()
{
    if (!IsValid(Loadout)) { return; }
    /*weaponController.CancelReady();
    weaponController.activeWeapons.Clear();*/

    EquipToPrimaryHolster(Loadout->GetItemFromEquipmentSlot(PrimaryWeapon));
    EquipToSecondaryHolster(Loadout->GetItemFromEquipmentSlot(SecondaryWeapon));
    EquipToBackHolster(Loadout->GetItemFromEquipmentSlot(TertiaryWeapon));

    EquipToLethalHolster(Loadout->GetItemFromEquipmentSlot(LethalEquipment));
    EquipToTacticalHolster(Loadout->GetItemFromEquipmentSlot(TacticalEquipment));
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
        UE_LOG(LogTemp, Log, TEXT("Instantiating Primary Weapon []]..."));
        Loadout->PrimaryWeaponInstance = GetWorld()->SpawnActor<ATPSEquipableItem>(Loadout->primaryWeapon);
    }
    /*
    if (Loadout->GetItemFromEquipmentSlot(SecondaryWeapon)) {
        UE_LOG(LogTemp, Log, TEXT("Instantiating Secondary Weapon [%s]]..."), Loadout->secondaryWeapon);        //Loadout->secondaryWeapon = GameObject.Instantiate(Loadout->secondaryWeapon, transform);
        Loadout->secondaryWeapon = GetWorld()->SpawnActor<ATPSWeapon>();
    }

    if (Loadout->GetItemFromEquipmentSlot(TertiaryWeapon)) {
        UE_LOG(LogTemp, Log, TEXT("Instantiating Tertiary Weapon [%s]]..."), Loadout->tertiaryWeapon);
        Loadout->tertiaryWeapon = GetWorld()->SpawnActor<ATPSWeapon>();
    }

    if (Loadout->GetItemFromEquipmentSlot(TacticalEquipment)) {
        UE_LOG(LogTemp, Log, TEXT("Instantiating Tactical Equipment [%s]]..."), Loadout->tacticalEquipment);
        Loadout->tacticalEquipment = GetWorld()->SpawnActor<ATPSWeapon>();
    }

    if (Loadout->GetItemFromEquipmentSlot(LethalEquipment)) {
        UE_LOG(LogTemp, Log, TEXT("Instantiating Lethal Equipment [%s]]..."), Loadout->lethalEquipment);
        Loadout->lethalEquipment = GetWorld()->SpawnActor<ATPSWeapon>();
    }*/
}

void UTPSEquipmentManager::UnequipActive() {
    if (!IsValid(Loadout)) { return; }
    if (ActiveEquipmentSlot == ETPSEquipmentSlot::None) { return; }

    switch (ActiveEquipmentSlot) {
    case PrimaryWeapon:
        EquipToPrimaryHolster(Loadout->GetItemFromEquipmentSlot(PrimaryWeapon));
        break;
    case SecondaryWeapon:
        EquipToSecondaryHolster(Loadout->GetItemFromEquipmentSlot(SecondaryWeapon));
        break;
    case TertiaryWeapon:
        EquipToBackHolster(Loadout->GetItemFromEquipmentSlot(TertiaryWeapon));
        break;
    case LethalEquipment:
        EquipToLethalHolster(Loadout->GetItemFromEquipmentSlot(LethalEquipment));
        break;
    case TacticalEquipment:
        EquipToTacticalHolster(Loadout->GetItemFromEquipmentSlot(TacticalEquipment));
        break;
    case None:
    default:
        break;
    }

    //weaponController.activeWeapons.Clear();
    ActiveEquipmentSlot = ETPSEquipmentSlot::None;
}

void UTPSEquipmentManager::EquipAndArm(ETPSEquipmentSlot equipmentSlot) {
    if (!IsValid(Loadout)) { return; }

    ATPSEquipableItem* item = Loadout->GetItemFromEquipmentSlot(equipmentSlot);

    if (item) {
        EquipToPrimaryWeaponHand(item);
        //weaponController.activeWeapons.Add(weapon);
        ActiveEquipmentSlot = equipmentSlot;

        item->Equip();
    }
}