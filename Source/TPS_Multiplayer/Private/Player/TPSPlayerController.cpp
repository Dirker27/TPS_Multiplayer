// (C) ToasterCat Studios 2024


#include "Player/TPSPlayerController.h"

//~ ====================================================================== ~//
//- CONSOLE CONFIGURATION
//~ ====================================================================== ~//

static TAutoConsoleVariable<int32> CVarLocalPlayerDebugMode(
	TEXT("TPS.LocalPlayerDebugMode"),
	0,
	TEXT("Shows debug mode for local player.\n")
	TEXT("<=0: OFF\n")
	TEXT("  1: ON\n"));
static TAutoConsoleVariable<int32> CVarLocalPlayerCourchToggleMode(
	TEXT("TPS.LocalPlayerGodMode"),
	0,
	TEXT("Enables GOD MODE for local player.\n")
	TEXT("<=0: OFF\n")
	TEXT("  1: ON\n"));
static TAutoConsoleVariable<int32> CVarLocalPlayerGodMode(
	TEXT("TPS.LocalPlayerGodMode"),
	0,
	TEXT("Enables GOD MODE for local player.\n")
	TEXT("<=0: OFF\n")
	TEXT("  1: ON\n"));

void _OnControllerConfiugrationConsoleInput(IConsoleVariable* Var) {
	UE_LOG(LogTemp, Log, TEXT("Performing CONFIG Update..."));

	FTPSControllerConfiguration configuration = {
		CVarLocalPlayerDebugMode->GetInt(),
		CVarLocalPlayerGodMode->GetBool(),
		CVarLocalPlayerCourchToggleMode->GetBool()
	};
	UE_LOG(LogTemp, Log, TEXT("INPUT CharacterDEBUG: %i\nINPUT GodMode: %b"),
		configuration.localCharacterDebugMode, configuration.godModeEnabled);
	ATPSPlayerController::UpdateControllerConfiguration(&configuration);
}
void ATPSPlayerController::BindConsoleCallbacks() {
	CVarLocalPlayerDebugMode.AsVariable()
		->SetOnChangedCallback(FConsoleVariableDelegate::CreateLambda(&_OnControllerConfiugrationConsoleInput));
	CVarLocalPlayerCourchToggleMode.AsVariable()
		->SetOnChangedCallback(FConsoleVariableDelegate::CreateStatic(&_OnControllerConfiugrationConsoleInput));
	CVarLocalPlayerGodMode.AsVariable()
		->SetOnChangedCallback(FConsoleVariableDelegate::CreateStatic(&_OnControllerConfiugrationConsoleInput));

	_OnControllerConfiugrationConsoleInput(nullptr); // <- perform initial read (hacky)
}
FTPSControllerConfiguration* ATPSPlayerController::configuration = new FTPSControllerConfiguration();
void ATPSPlayerController::UpdateControllerConfiguration(FTPSControllerConfiguration* config) {
	configuration->localCharacterDebugMode = config->localCharacterDebugMode;
	configuration->godModeEnabled = config->godModeEnabled;
}

//~ ====================================================================== ~//
//- State Overrides
//~ ====================================================================== ~//

void ATPSPlayerController::TPS_OverrideCurrentCharacterStateFromString(FString input) {
	ETPSCharacterState newState = ETPSCharacterStateFromString(TCHAR_TO_ANSI(*input));
	UE_LOG(LogTemp, Log, TEXT("DEBUG OVERRIDE: CharacterState -> [%s]-[%i]"), TCHAR_TO_ANSI(*input), newState);
	OnCharacterStateOverride(newState);
}
void ATPSPlayerController::TPS_OverrideCurrentCharacterStateFromInt(int32 input) {
	ETPSCharacterState newState = ETPSCharacterState(input);
	UE_LOG(LogTemp, Log, TEXT("DEBUG OVERRIDE: CharacterState -> [%i]-[%i]"), input, newState);
	OnCharacterStateOverride(newState);
}
void ATPSPlayerController::Kill() {
	OnCharacterStateOverride(Incapacitated);
}
void ATPSPlayerController::Injure() {
	OnCharacterStateOverride(Injured);
}
void ATPSPlayerController::EnterCombat() {
	OnCharacterStateOverride(Combat);
}
void ATPSPlayerController::ExitCombat() {
	OnCharacterStateOverride(Casual);
}

void ATPSPlayerController::TPS_ToggleDebugForLocalPlayer() {	
	IsDebugEnabled = (!IsDebugEnabled);
	configuration->localCharacterDebugMode = (configuration->localCharacterDebugMode == 1)
		? 0
		: 1;
}
void ATPSPlayerController::DebugLocal() {
	TPS_ToggleDebugForLocalPlayer();
}


void ATPSPlayerController::TPS_ToggleCrouchForLocalPlayer() {
	IsDebugEnabled = (!IsDebugEnabled);
	configuration->crouchToggle = (configuration->crouchToggle == 1)
		? 0
		: 1;
}
void ATPSPlayerController::ToggleCrouch() {
	TPS_ToggleCrouchForLocalPlayer();
}