// (C) ToasterCat Studios 2025

#include "Weapon/Projectile/TPSProjectile.h"

#include "Kismet/KismetSystemLibrary.h"

ATPSProjectile::ATPSProjectile()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	SetRootComponent(CollisionComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CollisionComponent);

	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	if (ArrowComponent)
	{
		ArrowComponent->ArrowColor = FColor(200, 255, 200);
		ArrowComponent->bTreatAsASprite = true;
		ArrowComponent->SetupAttachment(CollisionComponent);
		ArrowComponent->bIsScreenSizeScaled = true;
		ArrowComponent->SetSimulatePhysics(false);
	}
}

void ATPSProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ATPSProjectile::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
}


void ATPSProjectile::Launch()
{
	FVector forward = GetActorForwardVector() * InitialVelocity;
	CollisionComponent->SetPhysicsLinearVelocity(forward, true, "None");

	OnLaunch();
}


AActor* ATPSProjectile::LineTrace(const UObject* WorldContextObject, const float deltaSeconds) {
	AActor* hitActor = NULL;

	FVector startLoc = GetActorLocation();
	FVector forward = GetActorForwardVector();

	float interpDistance = GetVelocity().Size() * 0.2f;

	FVector endLoc = startLoc + (forward * interpDistance);

	ETraceTypeQuery channel = TraceTypeQuery_MAX;
	TArray<AActor*> actorsToIgnore;
	EDrawDebugTrace::Type debugTrace = EDrawDebugTrace::Type::ForOneFrame;
	FHitResult hitResult;

	bool isHit = UKismetSystemLibrary::LineTraceSingle(WorldContextObject, startLoc, endLoc,
		channel, false, actorsToIgnore, debugTrace,
		hitResult,
		true,
		FLinearColor::Red, FLinearColor::Green, 5.f);

	if (isHit) {
		hitActor = hitResult.GetActor();
	}

	return hitActor;
}
