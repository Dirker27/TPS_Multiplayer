#include "Character/Attributes/StandardAttributeSet.h"

#include "GameplayEffectExtension.h"

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

void UStandardAttributeSet::OnRep_MovementSpeedMax(const FGameplayAttributeData& OldMovementSpeedMax) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UStandardAttributeSet, MovementSpeedMax, OldMovementSpeedMax);
}

void UStandardAttributeSet::OnRep_PrimaryAmmunition(const FGameplayAttributeData& OldPrimaryAmmunition) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UStandardAttributeSet, PrimaryAmmunition, OldPrimaryAmmunition);
}


void UStandardAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    // ?
}