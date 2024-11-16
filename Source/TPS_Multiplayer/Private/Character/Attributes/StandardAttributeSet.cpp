#include "Character/Attributes/StandardAttributeSet.h"

#include "GameplayEffectExtension.h"

#include "Net/UnrealNetwork.h"

void UStandardAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);
    
    // Update Health (between 0 and Max)
    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0, GetHealthMax());
    }
}

void UStandardAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    // Apply Damage (between 0 and Max)
    if (Data.EvaluatedData.Attribute == GetDamageAttribute())
    {
        const float LocalDamageDone = GetDamage();
        SetDamage(0);

        if (LocalDamageDone > 0) {
            const float NewHealth = GetHealth() - LocalDamageDone;
            SetHealth(FMath::Clamp(NewHealth, 0, GetHealthMax()));
        }
    }
}

void UStandardAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UStandardAttributeSet, Health, OldHealth);
}
void UStandardAttributeSet::OnRep_HealthMax(const FGameplayAttributeData& OldHealthMax) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UStandardAttributeSet, HealthMax, OldHealthMax);
}

void UStandardAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UStandardAttributeSet, Armor, OldArmor);
}
void UStandardAttributeSet::OnRep_ArmorMax(const FGameplayAttributeData& OldArmorMax) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UStandardAttributeSet, ArmorMax, OldArmorMax);
}

void UStandardAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UStandardAttributeSet, Stamina, OldStamina);
}
void UStandardAttributeSet::OnRep_StaminaMax(const FGameplayAttributeData& OldStaminaMax) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UStandardAttributeSet, StaminaMax, OldStaminaMax);
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

    DOREPLIFETIME_CONDITION_NOTIFY(UStandardAttributeSet, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UStandardAttributeSet, HealthMax, COND_None, REPNOTIFY_Always);
    
    DOREPLIFETIME_CONDITION_NOTIFY(UStandardAttributeSet, Armor, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UStandardAttributeSet, ArmorMax, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UStandardAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UStandardAttributeSet, StaminaMax, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UStandardAttributeSet, MovementSpeedModifier, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UStandardAttributeSet, AccuracyModifier, COND_None, REPNOTIFY_Always);
}