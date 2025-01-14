// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Behavior/TPSMountable.h"

#include "TPSEquipableItem.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API ATPSEquipableItem : public ATPSMountableActor
{
    GENERATED_BODY()

public:
    //ATPSEquipableItem();
    //~ATPSEquipableItem();

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
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FString Name;

    //- State --------------------------------------------=
    //
    //- IsActive
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    bool isActiveAndEnabled;

//~ ============================================================= ~//
//  BEHAVIOR
//~ ============================================================= ~//
public:
    //- Equipable -----------------------------------------=
    //
    UFUNCTION(BlueprintCallable)
    void Equip();
    UFUNCTION(BlueprintImplementableEvent)
    void OnEquip();
    //
    UFUNCTION(BlueprintCallable)
    void UnEquip();
    UFUNCTION(BlueprintImplementableEvent)
    void OnUnEquip();

    //- Usable ------------------------------------------=
    //  (TODO: Extract to UsableItem?)
    UFUNCTION(BlueprintCallable)
    void StartUse();
    UFUNCTION(BlueprintImplementableEvent)
    void OnStartUse();
    //
    UFUNCTION(BlueprintCallable)
    void StopUse();
    UFUNCTION(BlueprintImplementableEvent)
    void OnStopUse();
};