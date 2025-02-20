// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEC_DamageExecution.generated.h"

/**
 * 
 */
UCLASS()
class TPS_MULTIPLAYER_API UGEC_DamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UGEC_DamageExecution();

	// Called for each Tick of the effect's lifetime
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& execParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};
