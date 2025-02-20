#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"

#include "GAS/GASUtilities.h"

#include "CharacterHealthAttributeSet.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API UCharacterHealthAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    //- Health -------------------------------------------=
    //
    // Current Health
    UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing=OnRep_Health)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UCharacterHealthAttributeSet, Health);
    //
    UFUNCTION()
    void OnRep_Health(const FGameplayAttributeData& OldHealth);
    //
    // Max Health
    UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing=OnRep_HealthMax)
    FGameplayAttributeData HealthMax;
    ATTRIBUTE_ACCESSORS(UCharacterHealthAttributeSet, HealthMax);
    //
    UFUNCTION()
    void OnRep_HealthMax(const FGameplayAttributeData& OldHealthMax);
    //
    // Damage
    //   (server-side only)
    UPROPERTY(BlueprintReadOnly, Category = "Health|Damage")
    FGameplayAttributeData HealthDamage;
    ATTRIBUTE_ACCESSORS(UCharacterHealthAttributeSet, HealthDamage);
    

    //- Current Armor -------------------------------------=
    
    // Armor
    UPROPERTY(BlueprintReadOnly, Category = "Armor", ReplicatedUsing = OnRep_Armor)
    FGameplayAttributeData Armor;
    ATTRIBUTE_ACCESSORS(UCharacterHealthAttributeSet, Armor);
    //
    UFUNCTION()
    void OnRep_Armor(const FGameplayAttributeData& OldArmor);
    //
    // Max Armor
    UPROPERTY(BlueprintReadOnly, Category = "Armor", ReplicatedUsing = OnRep_ArmorMax)
    FGameplayAttributeData ArmorMax;
    ATTRIBUTE_ACCESSORS(UCharacterHealthAttributeSet, ArmorMax);
    //
    UFUNCTION()
    void OnRep_ArmorMax(const FGameplayAttributeData& OldArmorhMax);
    //
    // Damage
    //   (server-side only)
    UPROPERTY(BlueprintReadOnly, Category = "Armor|Damage")
    FGameplayAttributeData ArmorDamage;
    ATTRIBUTE_ACCESSORS(UCharacterHealthAttributeSet, ArmorDamage);
    // Armor Regeneration Rate
    //   (server-side only)
    UPROPERTY(BlueprintReadOnly, Category = "Armor|Regen")
    FGameplayAttributeData ArmorRegenRate;
    ATTRIBUTE_ACCESSORS(UCharacterHealthAttributeSet, ArmorRegenRate);
    //
    // Armor Regeneration Delay
    //   (server-side only)
    UPROPERTY(BlueprintReadOnly, Category = "Armor|Regen")
    FGameplayAttributeData ArmorRegenDelay;
    ATTRIBUTE_ACCESSORS(UCharacterHealthAttributeSet, ArmorRegenDelay);


    //- Stamina -------------------------------------------=
    
    // Current Stamina
    UPROPERTY(BlueprintReadOnly, Category = "Stamina", ReplicatedUsing = OnRep_Stamina)
    FGameplayAttributeData Stamina;
    ATTRIBUTE_ACCESSORS(UCharacterHealthAttributeSet, Stamina);
    //
    UFUNCTION()
    void OnRep_Stamina(const FGameplayAttributeData& OldStamina);
    //
    // Max Stamina
    UPROPERTY(BlueprintReadOnly, Category = "Stamina", ReplicatedUsing = OnRep_StaminaMax)
    FGameplayAttributeData StaminaMax;
    ATTRIBUTE_ACCESSORS(UCharacterHealthAttributeSet, StaminaMax);
    //
    UFUNCTION()
    void OnRep_StaminaMax(const FGameplayAttributeData& OldStaminaMax);
    //
    // Stamina Regeneration Rate
    //   (server-side only)
    UPROPERTY(BlueprintReadOnly, Category = "Stamina|Regen")
    FGameplayAttributeData StaminaRegenRate;
    ATTRIBUTE_ACCESSORS(UCharacterHealthAttributeSet, StaminaRegenRate);
    //
    // Stamina Regeneration Delay
    //   (server-side only)
    UPROPERTY(BlueprintReadOnly, Category = "Stamina|Regen")
    FGameplayAttributeData StaminaRegenDelay;
    ATTRIBUTE_ACCESSORS(UCharacterHealthAttributeSet, StaminaRegenDelay);

    //~ ============================================================ ~//
    //  GAS PLUMBING
    //~ ============================================================ ~//
public:
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

