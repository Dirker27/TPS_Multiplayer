// (C) ToasterCat Studios 2024

#pragma once

#include "CoreMinimal.h"

#include "TPSGameConfiguration.generated.h"

USTRUCT(BlueprintType)
struct TPS_MULTIPLAYER_API FTPSGameConfiguration
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	int GlobalCharacterDebugMode = 0;

	UPROPERTY(BlueprintReadOnly)
	float GlobalFogDensity = 0.2;
};
