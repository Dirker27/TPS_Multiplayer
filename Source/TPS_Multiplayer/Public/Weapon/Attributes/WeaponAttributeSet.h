#pragma once

#include "CoreMinimal.h"

#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "Util/GASUtilities.h"
/*#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)*/

#include "WeaponAttributeSet.generated.h"


UCLASS()
class TPS_MULTIPLAYER_API UWeaponAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

//~ ============================================================= ~//
//  ATTRIBUTES
//~ ============================================================= ~//

public:

    //- Weapons ------------------------------------------=
    //
    //- Ammunition
    UPROPERTY(BlueprintReadOnly, Category = "Weapon}Ammunition", ReplicatedUsing = OnRep_Ammunition)
    FGameplayAttributeData Ammunition;
    ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Ammunition);
    //
    UFUNCTION()
    void OnRep_Ammunition(const FGameplayAttributeData& OldAmmunitionMax);
    //
    //- Ammunition Max (capacity)
    UPROPERTY(BlueprintReadOnly, Category = "Weapon|Ammunition", ReplicatedUsing = OnRep_AmmunitionMax)
    FGameplayAttributeData AmmunitionMax;
    ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, AmmunitionMax);
    //
    UFUNCTION()
    void OnRep_AmmunitionMax(const FGameplayAttributeData& OldAmmunitionMax);
    //
    //- Damage Modifier
    UPROPERTY(BlueprintReadOnly, Category = "Weapon|Behavior", ReplicatedUsing = OnRep_DamageModifier)
    FGameplayAttributeData DamageModifier;
    ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, DamageModifier);
    //
    UFUNCTION()
    void OnRep_DamageModifier(const FGameplayAttributeData& OldDamageModifier);
    //
    //- Accuracy Modifier
    UPROPERTY(BlueprintReadOnly, Category = "Weapon|Behavior", ReplicatedUsing = OnRep_AccuracyModifier)
    FGameplayAttributeData AccuracyModifier;
    ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, AccuracyModifier);
    //
    UFUNCTION()
    void OnRep_AccuracyModifier(const FGameplayAttributeData& OldAccuracyModifier);
    //
    //- Fire Rate Modifier
    UPROPERTY(BlueprintReadOnly, Category = "Weapon|Behavior", ReplicatedUsing = OnRep_FireRateModifier)
    FGameplayAttributeData FireRateModifier;
    ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, FireRateModifier);
    //
    UFUNCTION()
    void OnRep_FireRateModifier(const FGameplayAttributeData& OldFireRateModifier);
    //
    //- Reload Speed Modifier
    UPROPERTY(BlueprintReadOnly, Category = "Weapon|Behavior", ReplicatedUsing = OnRep_ReloadSpeedModifier)
    FGameplayAttributeData ReloadSpeedModifier;
    ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, ReloadSpeedModifier);
    //
    UFUNCTION()
    void OnRep_ReloadSpeedModifier(const FGameplayAttributeData& OldReloadSpeedModifier);

//~ ============================================================= ~//
//  GAS PLUMBING
//~ ============================================================= ~//
public:
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};