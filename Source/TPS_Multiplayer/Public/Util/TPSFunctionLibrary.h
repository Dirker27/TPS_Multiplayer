// (C) ToasterCat Studios 2024

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TPSFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TPS_MULTIPLAYER_API UTPSFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Actor", meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "ActorClass"))
	static AActor* GetNearestActorOfClass(const UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, FVector Location, float Radius = 512.f);

	UFUNCTION(BlueprintCallable, Category = "Debug")
	static void DrawDebugTrace(const UObject* WorldContextObject, const FVector startLoc, const FVector direction);
	static void DrawDebugTrace(const UObject* WorldContextObject, const FVector startLoc, const FVector direction,
		const FLinearColor traceColor, const FLinearColor hitColor, const float duration);

	// Calculates impulse in Joules from default unreal units
	//  Velocity = cm/s
	//  Mass = kg
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Physics")
	static FVector CalculateImpulseJoules(const FVector velocity, const float mass);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Physics")
	static FVector2D CalculateNoise2D(const float pitchDegrees, const float yawDegrees);
};
