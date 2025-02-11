// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPSAmmunitionType.generated.h"

// Compatability type (Chambering)
UENUM(BlueprintType)
enum ETPSAmmunitionType : int
{
	//- Pistol Cartridges ------------
	//
	// 9mm Luger
	NineMM_Luger,
	//
	// .45 ACP
	FortyFive_ACP,
	
	//- Rifle Cartridges -------------
	//
	// 5.56x45mm NATO
	FiveFiveSix_NATO,
	//
	// 7.62x51mm NATO
	SevenSixTwo_NATO,
	//
	// 7.62x39mm Russian
	SevenSixTwo_Russian,
	//
	// 5.45x39mm Russian
	FiveFourFive_Russian,
	//
	// 7.62x54mmR Mosin Nagant
	SevenSixTwo_Rimmed,
	//
	// 8mm Mauser
	EightMM_Mauser,

	//- Shotgun Cartridges -----------
	//
	// 12-Gauge
	TwelveGauge,
	// 20-Gauge
	Twenty_Gauge
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