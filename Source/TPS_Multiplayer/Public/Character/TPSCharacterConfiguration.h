// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"

#include "Character/TPSCharacterBodyType.h"

#include "TPSCharacterConfiguration.generated.h"


UCLASS()
class TPS_MULTIPLAYER_API UTPSCharacterConfiguration : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TEnumAsByte<ETPSCharacterBodyType> CharacterBodyType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BaseAccuracyTolerance;
};