#include "GAS/Attributes/WeaponAttributeSet.h"

#include "GameplayEffectExtension.h"

#include "Net/UnrealNetwork.h"

void UWeaponAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);
    
    // Update Health (between 0 and Max)
    if (Attribute == GetAmmunitionAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0, GetAmmunitionMax());
    }
}

void UWeaponAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);
}


void UWeaponAttributeSet::OnRep_Ammunition(const FGameplayAttributeData& OldAmmunition) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, Ammunition, OldAmmunition);
}
void UWeaponAttributeSet::OnRep_AmmunitionMax(const FGameplayAttributeData& OldAmmunitionMax) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, AmmunitionMax, OldAmmunitionMax);
}
void UWeaponAttributeSet::OnRep_DamageModifier(const FGameplayAttributeData& OldDamageModifier) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, DamageModifier, OldDamageModifier);
}
void UWeaponAttributeSet::OnRep_AccuracyModifier(const FGameplayAttributeData& OldAccuracyModifier) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, AccuracyModifier, OldAccuracyModifier);
}
void UWeaponAttributeSet::OnRep_FireRateModifier(const FGameplayAttributeData& OldFireRateModifier) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, FireRateModifier, OldFireRateModifier);
}
void UWeaponAttributeSet::OnRep_ReloadSpeedModifier(const FGameplayAttributeData& OldReloadSpeedModifier) {
    GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, ReloadSpeedModifier, OldReloadSpeedModifier);
}


void UWeaponAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, Ammunition, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, AmmunitionMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, DamageModifier, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, FireRateModifier, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, ReloadSpeedModifier, COND_None, REPNOTIFY_Always);
}