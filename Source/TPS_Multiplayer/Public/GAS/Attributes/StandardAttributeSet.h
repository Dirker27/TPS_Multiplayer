#pragma once

#include "CoreMinimal.h"

#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "GAS/GASUtilities.h"

#include "StandardAttributeSet.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API UStandardAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

//~ ============================================================= ~//
//  ATTRIBUTES
//~ ============================================================= ~//
public:
    //- Movement -----------------------------------------=
    //
    //- Movement Speed Modifier
    UPROPERTY(BlueprintReadOnly, Category = "Movement", ReplicatedUsing = OnRep_MovementSpeedModifier)
    FGameplayAttributeData MovementSpeedModifier;
    ATTRIBUTE_ACCESSORS(UStandardAttributeSet, MovementSpeedModifier);
    //
    UFUNCTION()
    void OnRep_MovementSpeedModifier(const FGameplayAttributeData& OldMovementSpeedModifier);
    

//~ ============================================================= ~//
//  GAS PLUMBING
//~ ============================================================= ~//
public:
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};