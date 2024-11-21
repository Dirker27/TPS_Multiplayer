#include "Character/Attributes/StandardAttributeSet.h"

#include "GameplayEffectExtension.h"

#include "Net/UnrealNetwork.h"

void UStandardAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);
}

void UStandardAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);
}

void UStandardAttributeSet::OnRep_MovementSpeedModifier(const FGameplayAttributeData& OldMovementSpeedModifier) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UStandardAttributeSet, MovementSpeedModifier, OldMovementSpeedModifier);
}

void UStandardAttributeSet::OnRep_AccuracyModifier(const FGameplayAttributeData& OldAccuracyModifier) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UStandardAttributeSet, AccuracyModifier, OldAccuracyModifier);
}


void UStandardAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(UStandardAttributeSet, MovementSpeedModifier, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UStandardAttributeSet, AccuracyModifier, COND_None, REPNOTIFY_Always);
}