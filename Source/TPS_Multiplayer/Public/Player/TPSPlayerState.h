// (C) ToasterCat Studios 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

#include "GAS/Attributes/StandardAttributeSet.h"
#include "GAS/Attributes/CharacterHealthAttributeSet.h"
#include "GAS/Attributes/WeaponAttributeSet.h"

#include "TPSPlayerState.generated.h"


UCLASS()
class TPS_MULTIPLAYER_API ATPSPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATPSPlayerState();
	~ATPSPlayerState();

protected:
	virtual void BeginPlay() override;

//~ ============================================================= ~//
//  ABILITY SYSTEM WIRING
//~ ============================================================= ~//
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override; // IAbilitySystemInterface

	UPROPERTY(VisibleAnywhere, Category = "Abilities|Attributes", Transient)
	UStandardAttributeSet* StandardAttributes{ nullptr };

	UPROPERTY(VisibleAnywhere, Category = "Abilities|Attributes", Transient)
    UCharacterHealthAttributeSet* CharacterHealthAttributes{ nullptr };

    UPROPERTY(VisibleAnywhere, Category = "Abilities|Attributes", Transient)
    UWeaponAttributeSet* WeaponAttributes{ nullptr };

protected:
	UPROPERTY(VisibleAnywhere, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent{ nullptr };
};
