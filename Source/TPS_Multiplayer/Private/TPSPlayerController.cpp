// (C) ToasterCat Studios 2024


#include "TPSPlayerController.h"

static TAutoConsoleVariable<int32> CVarLocalPlayerDebugMode(
	TEXT("TPS.LocalPlayerDebugMode"),
	0,
	TEXT("Shows debug mode for local player.\n")
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

	FTPSCharacterConfiguration configuration = {
		CVarLocalPlayerDebugMode->GetInt(),
		CVarLocalPlayerGodMode->GetBool()
	};
	UE_LOG(LogTemp, Log, TEXT("INPUT CharacterDEBUG: %i\nINPUT GodMode: %b"),
		configuration.localCharacterDebugMode, configuration.godModeEnabled);
	ATPSPlayerController::UpdateConfiguration(&configuration);
}
void ATPSPlayerController::BindConsoleCallbacks() {
	CVarLocalPlayerDebugMode.AsVariable()
		->SetOnChangedCallback(FConsoleVariableDelegate::CreateStatic(&_OnControllerConfiugrationConsoleInput));
	CVarLocalPlayerGodMode.AsVariable()
		->SetOnChangedCallback(FConsoleVariableDelegate::CreateStatic(&_OnControllerConfiugrationConsoleInput));

	_OnControllerConfiugrationConsoleInput(nullptr); // <- perform initial read (hacky)
}
FTPSCharacterConfiguration* ATPSPlayerController::configuration = new FTPSCharacterConfiguration();
void ATPSPlayerController::UpdateConfiguration(FTPSCharacterConfiguration* config) {
	configuration->localCharacterDebugMode = config->localCharacterDebugMode;
	configuration->godModeEnabled = config->godModeEnabled;
}

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

void ATPSPlayerController::TPS_ShowDebugForLocalPlayer() {
	UE_LOG(LogTemp, Log, TEXT("DebugForLocalPlayer: %i"), CVarLocalPlayerDebugMode.GetValueOnGameThread());
}

void ATPSPlayerController::OnDebugInputDelegate(IConsoleVariable* Var) {
	UE_LOG(LogTemp, Log, TEXT("-DEBUG INPUT-: %i"), Var->GetInt());
	OnDebugInput();
}