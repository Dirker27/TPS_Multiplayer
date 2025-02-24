// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Character/TPSCharacterState.h"
#include "TPSControllerConfiguration.h"

#include "TPSPlayerController.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API ATPSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	// Show DEBUG view to local player.
	UPROPERTY(BlueprintReadOnly)
	bool IsDebugEnabled = false;

//~ ==================================================================== ~//
//  CONSOLE COMMANDS (Developer-only API)
//~ ==================================================================== ~//
public:

	////////////////////////////////////////////////////////
	// Override Character State

	UFUNCTION(Exec, Category="Debug|Overrides")
	void TPS_OverrideCurrentCharacterStateFromInt(int32 state);
	//
	UFUNCTION(Exec, Category = "Debug|Overrides")
	void TPS_OverrideCurrentCharacterStateFromString(FString state);
	//
	UFUNCTION(Exec, Category = "Debug|Overrides")
	void Kill();
	//
	UFUNCTION(Exec, Category = "Debug|Overrides")
	void Injure();
	//
	UFUNCTION(Exec, Category = "Debug|Overrides")
	void EnterCombat();
	//
	UFUNCTION(Exec, Category = "Debug|Overrides")
	void ExitCombat();


	////////////////////////////////////////////////////////
	// Override Controller Configurations

	UFUNCTION(Exec, Category="Config|Controls")
	void TPS_ToggleCrouchForLocalPlayer();
	UFUNCTION(Exec, Category = "Config|Controls")
	void ToggleCrouch();


	////////////////////////////////////////////////////////
	// Visual Debugging

	UFUNCTION(Exec, Category="Debug|Visibility")
	void TPS_ToggleDebugForLocalPlayer();
	UFUNCTION(Exec, Category = "Debug|Visibility")
	void DebugLocal();


	////////////////////////////////////////////////////////
	// Character / Pawn Controls

	UFUNCTION(Exec, Category = "Pawn|Possess")
	void TPS_PossessNearestPlayablePawn();
	UFUNCTION(Exec, Category = "Pawn|Possess")
	void PossessPawn();

	UFUNCTION(Exec, Category = "Pawn|Possess")
	void TPS_UnPossessCurrentPawn();
	UFUNCTION(Exec, Category = "Pawn|Possess")
	void UnPossessPawn();

//~ ==================================================================== ~//
//  CONFIGURATION
//~ ==================================================================== ~//
public:

	UFUNCTION(BlueprintCallable)
	void BindConsoleCallbacks();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDebugInput();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCharacterStateOverride(ETPSCharacterState state);

	UFUNCTION(BlueprintCallable)
	static FTPSControllerConfiguration GetControllerConfiguration() {
		return *configuration;
	}
	static void UpdateControllerConfiguration(FTPSControllerConfiguration* config);

private:
	static FTPSControllerConfiguration* configuration;
};
