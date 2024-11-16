#include "Character/Attributes/WeaponAttributeSet.h"

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
    GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, Ammunition, OldAmmunitionMax);
}


void UWeaponAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, Ammunition, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, AmmunitionMax, COND_None, REPNOTIFY_Always);
}