#include "Character/Attributes/CharacterHealthAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void UCharacterHealthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    // Update Health (between 0 and Max)
    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0, GetHealthMax());
    }
}

void UCharacterHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    // Apply Health Damage (between 0 and Max)
    if (Data.EvaluatedData.Attribute == GetHealthDamageAttribute())
    {
        const float LocalDamageDone = GetHealthDamage();
        SetHealthDamage(0);

        if (LocalDamageDone > 0) {
            const float NewHealth = GetHealth() - LocalDamageDone;
            SetHealth(FMath::Clamp(NewHealth, 0, GetHealthMax()));
        }
    }

    // Apply Armor Damage (between 0 and Max)
    if (Data.EvaluatedData.Attribute == GetArmorDamageAttribute())
    {
        const float LocalDamageDone = GetArmorDamage();
        SetArmorDamage(0);

        if (LocalDamageDone > 0) {
            const float NewArmor = GetArmor() - LocalDamageDone;
            SetHealth(FMath::Clamp(NewArmor, 0, GetArmorMax()));
        }
    }
}

void UCharacterHealthAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterHealthAttributeSet, Health, OldHealth);
}
void UCharacterHealthAttributeSet::OnRep_HealthMax(const FGameplayAttributeData& OldHealthMax) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterHealthAttributeSet, HealthMax, OldHealthMax);
}

void UCharacterHealthAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterHealthAttributeSet, Armor, OldArmor);
}
void UCharacterHealthAttributeSet::OnRep_ArmorMax(const FGameplayAttributeData& OldArmorMax) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterHealthAttributeSet, ArmorMax, OldArmorMax);
}

void UCharacterHealthAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterHealthAttributeSet, Stamina, OldStamina);
}
void UCharacterHealthAttributeSet::OnRep_StaminaMax(const FGameplayAttributeData& OldStaminaMax) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterHealthAttributeSet, StaminaMax, OldStaminaMax);
}

void UCharacterHealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(UCharacterHealthAttributeSet, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UCharacterHealthAttributeSet, HealthMax, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UCharacterHealthAttributeSet, Armor, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UCharacterHealthAttributeSet, ArmorMax, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UCharacterHealthAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UCharacterHealthAttributeSet, StaminaMax, COND_None, REPNOTIFY_Always);
}