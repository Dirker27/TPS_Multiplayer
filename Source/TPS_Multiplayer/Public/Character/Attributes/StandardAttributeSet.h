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

public:

    //- Health -------------------------------------------=
    //
    // Current
    UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing=OnRep_Health)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, Health);
    //
    // Max
    UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing=OnRep_HealthMax)
    FGameplayAttributeData HealthMax;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, HealthMax);
    //
    // Damage
    //  (server-side only)
    UPROPERTY(BlueprintReadOnly, Category = "Damage")
    FGameplayAttributeData Damage;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, Damage);


    //- Movement -----------------------------------------=
    //
    // TOOD: Delete
    UPROPERTY(BlueprintReadOnly, Category = "Movement", ReplicatedUsing = OnRep_MovementSpeedMax)
    FGameplayAttributeData MovementSpeedMax;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, MovementSpeedMax);
    //
    // Modifier
    UPROPERTY(BlueprintReadOnly, Category = "Movement", ReplicatedUsing = OnRep_MovementSpeedModifier)
    FGameplayAttributeData MovementSpeedModifier;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, MovementSpeedModifier);


    //- Weapons ------------------------------------------=
    //
    // Accuracy Modifier
    UPROPERTY(BlueprintReadOnly, Category = "Weapons", ReplicatedUsing = OnRep_AccuracyModifier)
    FGameplayAttributeData AccuracyModifier;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, AccuracyModifier);
    //
    UPROPERTY(BlueprintReadOnly, Category = "Weapons.Ammunition", ReplicatedUsing = OnRep_PrimaryAmmunition)
    FGameplayAttributeData PrimaryAmmunition;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, PrimaryAmmunition);


    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;


    UFUNCTION()
    void OnRep_Health(const FGameplayAttributeData& OldHealth);

    UFUNCTION()
    void OnRep_HealthMax(const FGameplayAttributeData& OldHealthMax);

    // TODO: Delete
    UFUNCTION()
    void OnRep_MovementSpeedMax(const FGameplayAttributeData& OldMovementSpeedMax);

    UFUNCTION()
    void OnRep_MovementSpeedModifier(const FGameplayAttributeData& OldMovementSpeedModifier);

    UFUNCTION()
    void OnRep_AccuracyModifier(const FGameplayAttributeData& OldAccuracyModifier);

    UFUNCTION()
    void OnRep_PrimaryAmmunition(const FGameplayAttributeData& OldPrimaryAmmunition);


    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};