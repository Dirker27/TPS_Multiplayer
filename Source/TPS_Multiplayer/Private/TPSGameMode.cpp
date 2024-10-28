// (C) ToasterCat Studios 2024

#include "TPSGameMode.h"

//~ ====================================================================== ~//
//- CONSOLE CONFIGURATION
//~ ====================================================================== ~//

static TAutoConsoleVariable<int32> CVarGlobalCharacterDebugMode(
	TEXT("TPS.GlobalCharacterDebugMode"),
	0,
	TEXT("Shows debug mode for all active characters.\n")
	TEXT("<=0: OFF\n")
	TEXT("  1: ON\n"));
static TAutoConsoleVariable<int32> CVarGlobalFogDensity(
	TEXT("TPS.GlobalFogDensity"),
	0,
	TEXT("How dense fog should be for the shared map environment.\n")
	TEXT("<=0.0: Transparent\n")
	TEXT("  0.2: Typical\n")
	TEXT("  1.0: Opaque\n"));


void _OnGameConfiugrationConsoleInput(IConsoleVariable* Var) {
	UE_LOG(LogTemp, Log, TEXT("Performing CONFIG Update..."));

	FTPSGameConfiguration configuration = {
		CVarGlobalCharacterDebugMode->GetInt(),
		CVarGlobalFogDensity->GetFloat()
	};
	UE_LOG(LogTemp, Log, TEXT("INPUT CharacterDEBUG: %i\nINPUT FogDensity: %f"),
		configuration.globalCharacterDebugMode, configuration.globalFogDensity);
	ATPSGameMode::UpdateGameConfiguration(&configuration);
}
void ATPSGameMode::BindConsoleCallbacks() {
	CVarGlobalFogDensity.AsVariable()
		->SetOnChangedCallback(FConsoleVariableDelegate::CreateStatic(&_OnGameConfiugrationConsoleInput));
	CVarGlobalCharacterDebugMode.AsVariable()
		->SetOnChangedCallback(FConsoleVariableDelegate::CreateStatic(&_OnGameConfiugrationConsoleInput));

	_OnGameConfiugrationConsoleInput(nullptr); // <- perform initial read (hacky)
}
FTPSGameConfiguration* ATPSGameMode::configuration = new FTPSGameConfiguration(); //{ 0, 0.2f };
void ATPSGameMode::UpdateGameConfiguration(FTPSGameConfiguration* config) {
	configuration->globalCharacterDebugMode = config->globalCharacterDebugMode;
	configuration->globalFogDensity = config->globalFogDensity;
}


//~ ====================================================================== ~//
//- CONSTRUCTORS
//~ ====================================================================== ~//

ATPSGameMode::ATPSGameMode() { }
ATPSGameMode::~ATPSGameMode() { }


//~ ====================================================================== ~//
//- Operations
//~ ====================================================================== ~//

bool ATPSGameMode::RequestRespawn() {
	return true;
}

void ATPSGameMode::PerformRespawn(ATPSPlayerController playerController) {
	// TODO
}


//~ ====================================================================== ~//
//- Utilities
//~ ====================================================================== ~//

void ATPSGameMode::ShowDebugForAll() {
	UE_LOG(LogTemp, Log, TEXT("Debug Mode for ALL Characters: %i"), CVarGlobalCharacterDebugMode.GetValueOnGameThread());
}
