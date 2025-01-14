// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"

//#include "Behavior/TPSMountableActor.h"

#include "TPSMountPoint.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API UTPSMountPoint : public USceneComponent
{
    GENERATED_BODY()

public:
    UTPSMountPoint();
    //UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
    //TArray<ATPSMountableActor*> MountedActors;

#if WITH_EDITORONLY_DATA
/** Component shown in the editor only to indicate character facing */
    UPROPERTY()
    TObjectPtr<USphereComponent> SphereComponent;
#endif

//~ ============================================================= ~//
//  BEHAVIOR
//~ ============================================================= ~//
public:
    UFUNCTION(BlueprintCallable)
    FVector GetCurrentPosition() const;
    UFUNCTION(BlueprintCallable)
    FRotator GetCurrentRotation() const;
};