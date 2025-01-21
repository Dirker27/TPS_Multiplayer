// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPSAmmunitionModifierType.generated.h"

// Compatability type (Chambering)
UENUM(BlueprintType)
enum ETPSAmmunitionType : int
{
	NineMM_Luger,
	FortyFive_ACP,

	FiveFiveSix_NATO,
	SevenSixTwo_NATO,

	SevenSixTwo_Russian,
	FiveFourFive_Russian,

	SevenSixTwo_Rimmed,
	EightMM_Mauser
};

static const char* ETPSAmmunitionTypeToString(const ETPSAmmunitionType type) {
	switch (type) {
	case NineMM_Luger:
		return "9mm Luger";
	case FortyFive_ACP:
		return ".45 ACP";
	case FiveFiveSix_NATO:
		return "5.56x45mm NATO";
	case SevenSixTwo_NATO:
		return "7.62x39mm NATO";
	default:
		return "UNSUPPORTED";
	}
}

// Ammo Behavior Type
UENUM(BlueprintType)
enum ETPSAmmunitionModifierType : int
{
	Standard = 0,
	FullMetalJacket = 1,
	HollowPoint = 2,
	ArmorPiercing = 3,
	Subsonic = 4
};

static const char* ETPSAmmunitionModifierTypeToString(const ETPSAmmunitionModifierType type) {
	switch (type) {
	case Standard:
		return "Standard";
	case FullMetalJacket:
		return "Full Metal Jacket";
	case HollowPoint:
		return "Hollow Point";
	case ArmorPiercing:
		return "Armor Piercing";
	case Subsonic:
		return "Sub-sonic";
	default:
		return "UNSUPPORTED";
	}
}