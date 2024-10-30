// (C) ToasterCat Studios 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "TPSPlayerController.h"
#include "TPSGameConfiguration.h"

#include "TPSGameMode.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API ATPSGameMode : public AGameMode
{
	GENERATED_BODY()	
public:
	ATPSGameMode();
	~ATPSGameMode();


	UPROPERTY(BlueprintReadOnly)
	bool IsDebugEnabled = false;


	//- Game Mode Functions ----------------------------------------=
	//
	// Respawn
	UFUNCTION(BlueprintCallable)
	bool RequestRespawn();
	void PerformRespawn(ATPSPlayerController playerController);


	//~ ==================================================================== ~//
	//  CONSOLE COMMANDS (Developer-only API)
	//~ ==================================================================== ~//

	//- Visual Debugging ------------------------------------------=
	//
	UFUNCTION(Exec, Category = "Debug.Visibility")
	void TPS_ToggleDebugForAllCharacters();
	UFUNCTION(Exec, Category = "Debug.Visibility")
	void DebugGlobal();

	//~ ==================================================================== ~//
	//  CONFIGURATION
	//~ ==================================================================== ~//

	UFUNCTION(BlueprintCallable)
	void BindConsoleCallbacks();

	UFUNCTION(BlueprintCallable)
	static FTPSGameConfiguration GetGameConfiguration() {
		return *configuration;
	}
	static void UpdateGameConfiguration(FTPSGameConfiguration* configuration);

private:
	static FTPSGameConfiguration* configuration;
};
