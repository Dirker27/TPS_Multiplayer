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

    UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing=OnRep_Health)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, Health);

    UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing=OnRep_HealthMax)
    FGameplayAttributeData HealthMax;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, HealthMax);

    // server-side only
    UPROPERTY(BlueprintReadOnly, Category = "Damage")
    FGameplayAttributeData Damage;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, Damage);

    UPROPERTY(BlueprintReadOnly, Category = "Movement", ReplicatedUsing = OnRep_MovementSpeedMax)
    FGameplayAttributeData MovementSpeedMax;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, MovementSpeedMax);

    UPROPERTY(BlueprintReadOnly, Category = "PrimaryAmmunition", ReplicatedUsing = OnRep_PrimaryAmmunition)
    FGameplayAttributeData PrimaryAmmunition;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, PrimaryAmmunition);


    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;


    UFUNCTION()
    void OnRep_Health(const FGameplayAttributeData& OldHealth);

    UFUNCTION()
    void OnRep_HealthMax(const FGameplayAttributeData& OldHealthMax);

    UFUNCTION()
    void OnRep_MovementSpeedMax(const FGameplayAttributeData& OldMovementSpeedMax);

    UFUNCTION()
    void OnRep_PrimaryAmmunition(const FGameplayAttributeData& OldPrimaryAmmunition);


    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};