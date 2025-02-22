#pragma once

#include "CoreMinimal.h"

#include "AbilitySystemComponent.h"

#include "Character/TPSCharacter.h"

#include "GAS/Attributes/StandardAttributeSet.h"
#include "GAS/Attributes/CharacterHealthAttributeSet.h"
#include "GAS/Attributes/WeaponAttributeSet.h"

#include "TPSAICharacter.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API ATPSAICharacter : public ATPSCharacter
{
    GENERATED_BODY()

public:
    ATPSAICharacter();

public:
    virtual void BeginPlay() override;

//~ ============================================================= ~//
//  ABILITY SYSTEM WIRING
//~ ============================================================= ~//

protected:
   	UPROPERTY(VisibleAnywhere, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent{ nullptr };

public:

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override; // IAbilitySystemInterface

    //////////////////////////////////////////////////////
    // GAS Attributes

	UPROPERTY(VisibleAnywhere, Category = "Abilities|Attributes", Transient)
	UStandardAttributeSet* StandardAttributes{ nullptr };

	UPROPERTY(VisibleAnywhere, Category = "Abilities|Attributes", Transient)
    UCharacterHealthAttributeSet* CharacterHealthAttributes{ nullptr };

    UPROPERTY(VisibleAnywhere, Category = "Abilities|Attributes", Transient)
    UWeaponAttributeSet* WeaponAttributes{ nullptr };
};

