// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"

#include "Behavior/TPSMountPoint.h"

#include "TPSInteractable.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API ATPSInteractable : public AActor
{
    GENERATED_BODY()

//~ ============================================================= ~//
//  ATTRIBUTES
//~ ============================================================= ~//
public:
    //- Configuration ------------------------------------=
    //
    //- Interaction Duration
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
    bool IsInstantInteract = false;
    //
    //- Interaction Duration
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
    float InteractionTimeSeconds = 1;

    //- State --------------------------------------------=
    //
    //- Enable/Disable
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
    bool InteractEnabled = true;
    //
    //- Enable/Disable
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
    float InteractDurationSeconds = 0;

//~ ============================================================= ~//
//  BEHAVIOR
//~ ============================================================= ~//
public:
    UFUNCTION(BlueprintCallable)
    void StartInteract() { OnStartInteract(); }
    UFUNCTION(BlueprintImplementableEvent)
    void OnStartInteract();

    UFUNCTION(BlueprintCallable)
    void CancelInteract() { OnCancelInteract(); }
    UFUNCTION(BlueprintImplementableEvent)
    void OnCancelInteract();

    UFUNCTION(BlueprintCallable)
    void CompleteInteract() { OnCompleteInteract(); }
    UFUNCTION(BlueprintImplementableEvent)
    void OnCompleteInteract();
};