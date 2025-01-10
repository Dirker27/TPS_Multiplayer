// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon/TPSWeaponType.h"

#include "TPSEquipmentSlot.generated.h"

UENUM(BlueprintType)
enum ETPSEquipmentSlot : int
{
	None = 0,
	PrimaryWeapon = 1,
	SecondaryWeapon = 2,
	TertiaryWeapon = 3,
	LethalThrowable = 4,
	TacticalThrowable = 5
};

static const char* ETPSEquipmentSlotToString(const ETPSEquipmentSlot slot) {
	switch (slot) {
	case None:
		return "None";
	case PrimaryWeapon:
		return "PrimaryWeapon";
	case SecondaryWeapon:
		return "SecondaryWeapon";
	case TertiaryWeapon:
		return "TertiaryWeapon";
	case LethalThrowable:
		return "LethalThrowable";
	case TacticalThrowable:
		return "TacticalThrowable";
	default:
		return "UNSUPPORTED";
	}
}