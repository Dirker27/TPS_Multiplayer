// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"

#include "TPSReticle.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API UTPSWeaponReticle : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UTexture2D> ClosedReticle;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UTexture2D> OpenReticle;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float ClosedScale = 0.5f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float OpenScale = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float ClosedOpacity = 1.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float OpenOpacity = 0.5f;
};