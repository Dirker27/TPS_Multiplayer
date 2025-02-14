// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Behavior/TPSMountPoint.h"
#include "Components/ArrowComponent.h"

#include "Weapon/Ammunition/TPSAmmunitionType.h"

#include "TPSProjectile.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API ATPSProjectile : public AActor
{
    GENERATED_BODY()

public:
    ATPSProjectile();

    // UE Implementables
protected:
    virtual void BeginPlay() override;
    virtual void Tick(float deltaSeconds) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<USphereComponent> CollisionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UStaticMeshComponent> Mesh;

#if WITH_EDITORONLY_DATA
    UPROPERTY()
    TObjectPtr<UArrowComponent> ArrowComponent;
#endif

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UTexture2D> HitDecal;

//~ ============================================================= ~//
//  ATTRIBUTES
//~ ============================================================= ~//
public:
    //- Identity -----------------------------------------=
    //
    //- Name
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FName Name;
    //- Type
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    TEnumAsByte<ETPSAmmunitionType> Type;


    //- Configuration ------------------------------------=
    //
    //- Configuration
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    float InitialVelocity; // [m/s]
    //- On-Hit Effects
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    TArray<TSubclassOf<UGameplayEffect>> AppliedEffects;
    //- On-Hit Effects
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    bool ShowCollisionTrace = true;

    //- State --------------------------------------------=
    //
    //- EquipmentOwner (who shot me?)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    AActor* OwningActor;
    //- Name
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    bool HasFired;

//~ ============================================================= ~//
//  BEHAVIOR
//~ ============================================================= ~//
public:
    UFUNCTION(BlueprintCallable)
    void Launch();
    UFUNCTION(BlueprintImplementableEvent)
    void OnLaunch();

protected:
    UFUNCTION(BlueprintCallable)
    bool DetectCollisionByLineTrace(const float deltaSeconds, FHitResult& outHitResult);

    UFUNCTION(BlueprintImplementableEvent)
    void OnCharacterHit(ATPSCharacter* character, FHitResult hit);

    UFUNCTION(BlueprintImplementableEvent)
    void OnSurfaceHit(AActor* actor, FHitResult hit);
};