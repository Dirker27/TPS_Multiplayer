// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

#include "TPSEquipableItem.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API ATPSEquipableItem : public AActor
{
    GENERATED_BODY()

public:
    ATPSEquipableItem();
    ~ATPSEquipableItem();

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
//  COMPONENTS
//~ ============================================================= ~//
public:
    UFUNCTION(BlueprintCallable)
    void Equip();
    UFUNCTION(BlueprintCallable)
    void UnEquip();
};