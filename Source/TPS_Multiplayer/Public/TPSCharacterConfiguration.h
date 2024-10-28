// (C) ToasterCat Studios 2024

#pragma once

#include "CoreMinimal.h"

#include "TPSCharacterConfiguration.generated.h"

// "Controller" configuration?
USTRUCT(BlueprintType)
struct TPS_MULTIPLAYER_API FTPSCharacterConfiguration
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	int localCharacterDebugMode = 0;

	UPROPERTY(BlueprintReadOnly)
	bool godModeEnabled = false;
};
