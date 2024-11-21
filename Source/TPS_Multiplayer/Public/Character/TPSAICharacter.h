#pragma once

#include "CoreMinimal.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

#include "Ability/AbilitySet.h"
#include "Character/TPSCharacter.h"
#include "Character/Attributes/StandardAttributeSet.h"
#include "Character/Attributes/CharacterHealthAttributeSet.h"
#include "Weapon/Attributes/WeaponAttributeSet.h"

#include "TPSAICharacter.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API ATPSAICharacter : public ATPSCharacter
{
    GENERATED_BODY()

public:
    ATPSAICharacter();
    ~ATPSAICharacter();

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

    //- GAS Attributes ------------------------------------=
    //
	UPROPERTY(VisibleAnywhere, Category = "Abilities.Attributes", Transient)
	UStandardAttributeSet* StandardAttributes{ nullptr };
    //
	UPROPERTY(VisibleAnywhere, Category = "Abilities.Attributes", Transient)
    UCharacterHealthAttributeSet* CharacterHealthAttributes{ nullptr };
    //
    UPROPERTY(VisibleAnywhere, Category = "Abilities.Attributes", Transient)
    UWeaponAttributeSet* WeaponAttributes{ nullptr };
};

