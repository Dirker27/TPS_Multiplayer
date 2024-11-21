#include "Ability/AbilitySet.h"

TArray<FGameplayAbilitySpecHandle> UAbilitySet::GrantAbilitiesToAbilitySystem(UAbilitySystemComponent* AbilitySystemComponent) const {
    check(AbilitySystemComponent);

    TArray<FGameplayAbilitySpecHandle> handles;
    handles.Reserve(AbilitySetItems.Num());

    for (const auto abilitySetItem : AbilitySetItems)
    {
        handles.AddUnique(AbilitySystemComponent->GiveAbility(
                FGameplayAbilitySpec(
                    abilitySetItem.GameplayAbility,
                    9,
                    static_cast<uint32>(abilitySetItem.InputKey)
                )
            ));
    }
    
    return handles;
}