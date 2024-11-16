#pragma once

#include "CoreMinimal.h"

#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "StandardAttributeSet.generated.h"


//#include "AttributeHelpers.h"
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class TPS_MULTIPLAYER_API UStandardAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

    //~ ============================================================ ~//
    //  ATTRIBUTES
    //~ ============================================================ ~//

public:

    //- Health -------------------------------------------=
    //
    //- Current Health
    UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing=OnRep_Health)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, Health);
    //
    UFUNCTION()
    void OnRep_Health(const FGameplayAttributeData& OldHealth);
    //
    //- Max Health
    UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing=OnRep_HealthMax)
    FGameplayAttributeData HealthMax;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, HealthMax);
    //
    UFUNCTION()
    void OnRep_HealthMax(const FGameplayAttributeData& OldHealthMax);
    //
    //- Current Armor
    UPROPERTY(BlueprintReadOnly, Category = "Health.Armor", ReplicatedUsing = OnRep_Armor)
    FGameplayAttributeData Armor;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, Armor);
    //
    UFUNCTION()
    void OnRep_Armor(const FGameplayAttributeData& OldArmor);
    //
    //- Max Armor
    UPROPERTY(BlueprintReadOnly, Category = "Health.Armor", ReplicatedUsing = OnRep_ArmorMax)
    FGameplayAttributeData ArmorMax;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, ArmorMax);
    //
    UFUNCTION()
    void OnRep_ArmorMax(const FGameplayAttributeData& OldArmorhMax);
    //
    //- Damage
    //   (server-side only)
    UPROPERTY(BlueprintReadOnly, Category = "Health.Damage")
    FGameplayAttributeData Damage;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, Damage);


    //- Stamina -------------------------------------------=
    //
    //- Current Stamina
    UPROPERTY(BlueprintReadOnly, Category = "Stamina", ReplicatedUsing = OnRep_Stamina)
    FGameplayAttributeData Stamina;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, Stamina);
    //
    UFUNCTION()
    void OnRep_Stamina(const FGameplayAttributeData& OldStamina);
    //
    //- Max Stamina
    UPROPERTY(BlueprintReadOnly, Category = "Stamina", ReplicatedUsing = OnRep_StaminaMax)
    FGameplayAttributeData StaminaMax;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, StaminaMax);
    //
    UFUNCTION()
    void OnRep_StaminaMax(const FGameplayAttributeData& OldStaminaMax);
    //
    //- Stamina Regeneration
    //   (server-side only)
    UPROPERTY(BlueprintReadOnly, Category = "Stamina.Regen", ReplicatedUsing = OnRep_StaminaRegen)
    FGameplayAttributeData StaminaRegen;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, StaminaRegen);


    //- Movement -----------------------------------------=
    //
    //- Movement Speed Modifier
    UPROPERTY(BlueprintReadOnly, Category = "Movement", ReplicatedUsing = OnRep_MovementSpeedModifier)
    FGameplayAttributeData MovementSpeedModifier;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, MovementSpeedModifier);
    //
    UFUNCTION()
    void OnRep_MovementSpeedModifier(const FGameplayAttributeData& OldMovementSpeedModifier);


    //- Weapon Handling ----------------------------------=
    // 
    //- Accuracy Modifier
    UPROPERTY(BlueprintReadOnly, Category = "Weapons", ReplicatedUsing = OnRep_AccuracyModifier)
    FGameplayAttributeData AccuracyModifier;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, AccuracyModifier);
    //
    UFUNCTION()
    void OnRep_AccuracyModifier(const FGameplayAttributeData& OldAccuracyModifier);
    

    //~ ============================================================ ~//
    //  GAS PLUMBING
    //~ ============================================================ ~//
public:
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};