#pragma once

#include "CoreMinimal.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

#include "Weapon/TPSWeaponType.h"
#include "Weapon/Attributes/WeaponAttributeSet.h"

#include "TPSWeapon.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API ATPSWeapon : public AActor, public IAbilitySystemInterface
{
    GENERATED_BODY()

    //~ ============================================================ ~//
    //  ATTRIBUTES
    //~ ============================================================ ~//

public:

    //- Identity ------------------------------------------=
    //
    //- Ammunition
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TEnumAsByte<ETPSWeaponType> Type;


    UPROPERTY(VisibleAnywhere, Category = "Abilities")
    UWeaponAttributeSet* WeaponAttributes{ nullptr };



public:
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override; // IAbilitySystemInterface

protected:
    UPROPERTY(Visibleanywhere, Category = "Abilities")
    UAbilitySystemComponent* AbilitySystemComponent{ nullptr };
};

