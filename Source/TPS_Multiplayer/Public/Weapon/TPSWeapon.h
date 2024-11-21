#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

#include "Weapon/TPSWeaponType.h"
#include "Weapon/Attributes/WeaponAttributeSet.h"

#include "TPSWeapon.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API ATPSWeapon : public AActor
{
    GENERATED_BODY()

public:
    ATPSWeapon();
    ~ATPSWeapon();

//~ ============================================================= ~//
//  COMPONENTS
//~ ============================================================= ~//
public:
    TObjectPtr<USkeletalMeshComponent> Mesh;

#if WITH_EDITORONLY_DATA
	/** Component shown in the editor only to indicate character facing */
	UPROPERTY()
	TObjectPtr<UArrowComponent> ArrowComponent;
#endif

//~ ============================================================= ~//
//  ATTRIBUTES
//~ ============================================================= ~//
public:
    //- Identity ------------------------------------------=
    //
    //- Name
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;
    // 
    //- Type
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TEnumAsByte<ETPSWeaponType> Type;

//~ ============================================================= ~//
//  Blueprint Extensions
//~ ============================================================= ~//
public:
    //- Transforms -------------------------------------------=
	//
	//- CharacterState
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FString WeaponTypeToFString(const ETPSWeaponType t) {
		return FString(ETPSWeaponTypeToString(t));
	};

};

