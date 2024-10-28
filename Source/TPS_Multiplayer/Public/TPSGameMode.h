// (C) ToasterCat Studios 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "TPSPlayerController.h"
#include "TPSConfiguration.h"

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


	//- Console Commands --------------------------------------------=
	//
	UFUNCTION(Exec)
	void ShowDebugForAll();



	UFUNCTION(BlueprintCallable)
	void BindConsoleCallbacks();


	UFUNCTION(BlueprintCallable)
	static FTPSConfiguration GetConfiguration() {
		return *configuration;
	}

	static void UpdateConfiguration(FTPSConfiguration* configuration);

private:
	static FTPSConfiguration* configuration;

	int globalDebugMode;
};
