// (C) ToasterCat Studios 2024


#include "Util/TPSFunctionLibrary.h"

#include <Kismet/GameplayStatics.h>

#include "Kismet/KismetMathLibrary.h"

AActor* UTPSFunctionLibrary::GetNearestActorOfClass(const UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, FVector Location, float Radius)
{
    AActor* NearestActor = NULL;

    float NearestDistance = Radius;

    TArray<AActor*> OutActors;
    UGameplayStatics::GetAllActorsOfClass(WorldContextObject, ActorClass, OutActors);

    for (AActor* Actor : OutActors) {
        float Distance = FVector::Distance(Location, Actor->GetActorLocation());

        if (Distance < NearestDistance)
        {
            NearestActor = Actor;
            NearestDistance = Distance;
        }
    }

    return NearestActor;
}

FVector2D UTPSFunctionLibrary::CalculateNoise2D(const float pitchDegrees, const float yawDegrees)
{
    FVector randomDirection = UKismetMathLibrary::RandomUnitVector();
    FVector2D offsetDirection = FVector2D(randomDirection.X, randomDirection.Y).GetSafeNormal(0.00001);

    float deltaPitch = UKismetMathLibrary::RandomFloatInRange(
        randomDirection.X * pitchDegrees * -1,
        randomDirection.X * pitchDegrees);
    float deltaYaw = UKismetMathLibrary::RandomFloatInRange(
        randomDirection.Y * yawDegrees * -1,
        randomDirection.Y * yawDegrees);

    return FVector2D(deltaPitch, deltaYaw);
}

FVector UTPSFunctionLibrary::CalculateImpulseJoules(const FVector velocity, const float mass)
{
    UE::Math::TVector<double> direction;
    float magnitude;
    velocity.ToDirectionAndLength(direction, magnitude);

    magnitude = magnitude / 100; // convert to m/s

    // KE == v^2 * (m/2)
    float joules = (magnitude * magnitude) * mass;

    FVector impulseVector = joules * direction;
    return impulseVector;
}

void UTPSFunctionLibrary::DrawDebugTrace(const UObject* WorldContextObject, const FVector startLoc, const FVector direction)
{
    UTPSFunctionLibrary::DrawDebugTrace(WorldContextObject, startLoc, direction,
        FLinearColor::MakeRandomColor(), FLinearColor::MakeRandomColor(), 1.f);
}
void UTPSFunctionLibrary::DrawDebugTrace(const UObject* worldContextObject,
                    const FVector startLoc,
                    const FVector direction,
                    const FLinearColor traceColor,
                    const FLinearColor hitColor,
                    const float duration)
{
    FVector endLoc = startLoc + direction;

    ETraceTypeQuery channel = TraceTypeQuery_MAX;
    TArray<AActor*> actorsToIgnore;
    EDrawDebugTrace::Type debugTrace = EDrawDebugTrace::Type::ForDuration;

    FHitResult hitResult;
    UKismetSystemLibrary::LineTraceSingle(worldContextObject, startLoc, endLoc,
        channel, false, actorsToIgnore, debugTrace,
        hitResult,
        true,
        traceColor, hitColor, duration);
}