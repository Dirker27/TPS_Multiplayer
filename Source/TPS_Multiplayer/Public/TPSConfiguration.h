// (C) ToasterCat Studios 2024

#pragma once

#include "CoreMinimal.h"

#include "TPSConfiguration.generated.h"

USTRUCT(BlueprintType)
struct TPS_MULTIPLAYER_API FTPSConfiguration
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	int globalCharacterDebugMode = 0;

	UPROPERTY(BlueprintReadOnly)
	float globalFogDensity = 0.2;
};
