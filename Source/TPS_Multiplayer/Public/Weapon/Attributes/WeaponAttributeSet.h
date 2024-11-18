#pragma once

#include "CoreMinimal.h"

#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "WeaponAttributeSet.generated.h"


//#include "AttributeHelpers.h"
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class TPS_MULTIPLAYER_API UWeaponAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

    //~ ============================================================ ~//
    //  ATTRIBUTES
    //~ ============================================================ ~//

public:

    //- Weapons ------------------------------------------=
    //
    //- Ammunition
    UPROPERTY(BlueprintReadOnly, Category = "Weapons.Ammunition", ReplicatedUsing = OnRep_Ammunition)
    FGameplayAttributeData Ammunition;
    ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Ammunition);
    //
    UFUNCTION()
    void OnRep_Ammunition(const FGameplayAttributeData& OldAmmunitionMax);
    //
    //- Ammunition Max (capacity)
    UPROPERTY(BlueprintReadOnly, Category = "Weapons.Ammunition", ReplicatedUsing = OnRep_AmmunitionMax)
    FGameplayAttributeData AmmunitionMax;
    ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, AmmunitionMax);
    //
    UFUNCTION()
    void OnRep_AmmunitionMax(const FGameplayAttributeData& OldAmmunitionMax);

    //~ ============================================================ ~//
    //  GAS PLUMBING
    //~ ============================================================ ~//
public:
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};