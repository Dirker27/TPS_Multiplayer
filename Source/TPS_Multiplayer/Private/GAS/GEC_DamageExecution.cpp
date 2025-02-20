// (C) ToasterCat Studios 2025


#include "GAS/GEC_DamageExecution.h"

#include "GAS/Attributes/CharacterHealthAttributeSet.h"
#include "GAS/Attributes/WeaponAttributeSet.h"

struct FDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Stamina);

	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageModifier);

	FDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterHealthAttributeSet, Health, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterHealthAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterHealthAttributeSet, Stamina, Target, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UWeaponAttributeSet, DamageModifier, Source, false);
	}
};

static const FDamageStatics& DamageStatics()
{
	static FDamageStatics DmgStatics;
	return DmgStatics;
}

UGEC_DamageExecution::UGEC_DamageExecution()
{
	RelevantAttributesToCapture.Add(DamageStatics().HealthDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().StaminaDef);

	RelevantAttributesToCapture.Add(DamageStatics().DamageModifierDef);
}

void UGEC_DamageExecution::Execute_Implementation(
												const FGameplayEffectCustomExecutionParameters& execParams,
												FGameplayEffectCustomExecutionOutput& outExecutionOutput) const
{
	// capture attributes
	UAbilitySystemComponent* sourceAsc = execParams.GetSourceAbilitySystemComponent();
	AActor* sourceActor = sourceAsc ? sourceAsc->GetAvatarActor() : nullptr;

	UAbilitySystemComponent* targetAsc = execParams.GetTargetAbilitySystemComponent();
	AActor* targetActor = targetAsc ? targetAsc->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& spec = execParams.GetOwningSpec();
	const FGameplayTagContainer* sourceTags = spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* targetTags = spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters evalParams;
	evalParams.SourceTags = sourceTags;
	evalParams.TargetTags = targetTags;

	// -----------------

	float baseDmg = FMath::Max<float>(spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("SetByCaller.DamageAmount")), false, -1.f), 0);

	float dmgModifier = 1.f;
	execParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DamageModifierDef, evalParams, dmgModifier);

	float targetHealth = 0;
	execParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, evalParams, targetHealth);

	float targetArmor = 0;
	execParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, evalParams, targetArmor);


	UE_LOG(LogTemp, Log, TEXT("Applying Damage:[%.2f]-Mod:[%.2f] to Health[%.2f]-Armor[%.2f]"),
		baseDmg, dmgModifier, targetHealth, targetArmor);

	float appliedDmg = (baseDmg * dmgModifier) * (1 - (targetArmor/100));
	if (appliedDmg < 0)
	{
		appliedDmg = 0;
	}

	UE_LOG(LogTemp, Log, TEXT("Applied Damage: [%.2f]"), appliedDmg);
	// return
	outExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HealthProperty, EGameplayModOp::Additive, -appliedDmg));
}
