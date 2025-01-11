// (C) ToasterCat Studios 2025

#include "Inventory/TPSEquipmentManager.h"

ATPSEquipmentManager::ATPSEquipmentManager() { }
ATPSEquipmentManager::~ATPSEquipmentManager() { }

void ATPSEquipmentManager::BeginPlay()
{
    InstantiateLoadout();

    EquipToPrimaryHolster(Loadout.GetWeaponFromEquipmentSlot(PrimaryWeapon));
    EquipToSecondaryHolster(Loadout.GetWeaponFromEquipmentSlot(SecondaryWeapon));
    EquipToBackHolster(Loadout.GetWeaponFromEquipmentSlot(TertiaryWeapon));

    EquipToLethalHolster(Loadout.GetWeaponFromEquipmentSlot(LethalThrowable));
    EquipToTacticalHolster(Loadout.GetWeaponFromEquipmentSlot(TacticalThrowable));

    ActiveEquipmentSlot = ETPSEquipmentSlot::None;
}

//~ ============================================================= ~//
//  EQUIPMENT OPERATIONS
//~ ============================================================= ~//

void ATPSEquipmentManager::EquipToPrimaryWeaponHand(ATPSWeapon* weapon)
{
	// Attach to parent bone
}

void ATPSEquipmentManager::EquipToSecondaryWeaponHand(ATPSWeapon* weapon)
{
	// Attach to parent bone
}

void ATPSEquipmentManager::EquipToPrimaryHolster(ATPSWeapon* weapon)
{
	// Attach to parent bone
}

void ATPSEquipmentManager::EquipToSecondaryHolster(ATPSWeapon* weapon)
{
	// Attach to parent bone
}

void ATPSEquipmentManager::EquipToTacticalHolster(ATPSWeapon* weapon)
{
	// Attach to parent bone
}

void ATPSEquipmentManager::EquipToLethalHolster(ATPSWeapon* weapon)
{
	// Attach to parent bone
}

void ATPSEquipmentManager::EquipToBackHolster(ATPSWeapon* weapon)
{
	// Attach to parent bone
}


//~ ============================================================= ~//
//  PUBLIC OPERATIONS
//~ ============================================================= ~//

void ATPSEquipmentManager::Ready()
{
    ActiveEquipmentSlot = ETPSEquipmentSlot::PrimaryWeapon;
    EquipToPrimaryWeaponHand(Loadout.GetWeaponFromEquipmentSlot(PrimaryWeapon));

    /*weaponController.activeWeapons.Add(Loadout.primaryWeapon);
    weaponController.Ready();*/
}

void ATPSEquipmentManager::UnReady()
{
    /*weaponController.CancelReady();
    weaponController.activeWeapons.Clear();*/

    EquipToPrimaryHolster(Loadout.GetWeaponFromEquipmentSlot(PrimaryWeapon));
    EquipToSecondaryHolster(Loadout.GetWeaponFromEquipmentSlot(SecondaryWeapon));
    EquipToBackHolster(Loadout.GetWeaponFromEquipmentSlot(TertiaryWeapon));

    EquipToLethalHolster(Loadout.GetWeaponFromEquipmentSlot(LethalThrowable));
    EquipToTacticalHolster(Loadout.GetWeaponFromEquipmentSlot(TacticalThrowable));
}

void ATPSEquipmentManager::EquipPrimary()
{
    UnequipActive();
    EquipAndArm(ETPSEquipmentSlot::PrimaryWeapon);
}

void ATPSEquipmentManager::EquipSecondary()
{
    UnequipActive();
    EquipAndArm(ETPSEquipmentSlot::SecondaryWeapon);
}

void ATPSEquipmentManager::EquipTertiary() {
    UnequipActive();
    EquipAndArm(ETPSEquipmentSlot::TertiaryWeapon);
}

void ATPSEquipmentManager::EquipLethalThrowable() {
    UnequipActive();
    EquipAndArm(ETPSEquipmentSlot::LethalThrowable);
}

void ATPSEquipmentManager::EquipTacticalThrowable() {
    UnequipActive();
    EquipAndArm(ETPSEquipmentSlot::TacticalThrowable);
}

void ATPSEquipmentManager::WeaponSwap() {
    UE_LOG(LogTemp, Log, TEXT("Swapping Weapons..."));

    // Needs to acct for non-populated slots.

    /*int nextSlot = ((int)ActiveEquipmentSlot) + 1 % 5;

    UnequipActive();
    EquipAndArm((ETPSEquipmentSlot) nextSlot);*/
}

void ATPSEquipmentManager::EquipmentSwap() {
    UE_LOG(LogTemp, Log, TEXT("Swapping Equipment..."));
}

void ATPSEquipmentManager::InstantiateLoadout() {
    if (Loadout.GetWeaponFromEquipmentSlot(PrimaryWeapon)) {
        UE_LOG(LogTemp, Log, TEXT("Instantiating Primary Weapon [", Loadout.primaryWeapon.name, "]..."));
        //Loadout.primaryWeapon = GEEngine->SpawnActor<ATPSWeapon>();
    }

    if (Loadout.GetWeaponFromEquipmentSlot(PrimaryWeapon)) {
        UE_LOG(LogTemp, Log, TEXT("Instantiating Secondary Weapon [", Loadout.secondaryWeapon.name, "]..."));
        //Loadout.secondaryWeapon = GameObject.Instantiate(Loadout.secondaryWeapon, transform);
    }

    if (Loadout.GetWeaponFromEquipmentSlot(TertiaryWeapon)) {
        UE_LOG(LogTemp, Log, TEXT("Instantiating Tertiary Weapon [", Loadout.tertiaryWeapon->name, "]..."));
        //Loadout.tertiaryWeapon = GameObject.Instantiate(Loadout.tertiaryWeapon, std::transform);
    }

    if (Loadout.GetWeaponFromEquipmentSlot(TacticalThrowable)) {
        UE_LOG(LogTemp, Log, TEXT("Instantiating Tactical Throwable [", Loadout.primaryWeapon.name, "]..."));
        //Loadout.tacticalThrowable = GameObject.Instantiate(Loadout.tacticalThrowable, transform);
    }

    if (Loadout.GetWeaponFromEquipmentSlot(LethalThrowable)) {
        UE_LOG(LogTemp, Log, TEXT("Instantiating Lethal Throwable [", Loadout.primaryWeapon.name, "]..."));
        //Loadout.lethalThrowable = GameObject.Instantiate(Loadout.lethalThrowable, transform);
    }
}

void ATPSEquipmentManager::UnequipActive() {
    if (ActiveEquipmentSlot == ETPSEquipmentSlot::None) { return; }

    switch (ActiveEquipmentSlot) {
    case PrimaryWeapon:
        EquipToPrimaryHolster(Loadout.GetWeaponFromEquipmentSlot(PrimaryWeapon));
        break;
    case SecondaryWeapon:
        EquipToSecondaryHolster(Loadout.GetWeaponFromEquipmentSlot(SecondaryWeapon));
        break;
    case TertiaryWeapon:
        EquipToBackHolster(Loadout.GetWeaponFromEquipmentSlot(TertiaryWeapon));
        break;
    case LethalThrowable:
        EquipToLethalHolster(Loadout.GetWeaponFromEquipmentSlot(LethalThrowable));
        break;
    case TacticalThrowable:
        EquipToTacticalHolster(Loadout.GetWeaponFromEquipmentSlot(TacticalThrowable));
        break;
    case None:
    default:
        break;
    }

    //weaponController.activeWeapons.Clear();
    ActiveEquipmentSlot = ETPSEquipmentSlot::None;
}

void ATPSEquipmentManager::EquipAndArm(ETPSEquipmentSlot equipmentSlot) {
    ATPSWeapon* weapon = Loadout.GetWeaponFromEquipmentSlot(equipmentSlot);

    if (weapon) {
        EquipToPrimaryWeaponHand(weapon);
        //weaponController.activeWeapons.Add(weapon);
        ActiveEquipmentSlot = equipmentSlot;

        weapon->Equip();
    }
}