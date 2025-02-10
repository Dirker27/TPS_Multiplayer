#pragma once

//#include "string.h"

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

#include "TPSWeaponState.generated.h"

UENUM(BlueprintType)
enum ETPSWeaponState
{
    Ready,
    Firing,
    Arming
};

static std::unordered_map<char*, ETPSWeaponState> ETPSWeaponStateMap{
    { "Ready", Ready },
    { "Firing", Firing },
    { "Arming", Arming }
};

static const ETPSWeaponState ETPSWeaponStateFromString(char* state) {
    return ETPSWeaponStateMap[state];
}

static const char* ETPSWeaponStateToString(const ETPSWeaponState state) {
    switch (state) {
    case Ready:
        return "Ready";
    case Firing:
        return "Firing";
    case Arming:
        return "Arming";
    default:
        return "UNSUPPORTED";
    }
}
