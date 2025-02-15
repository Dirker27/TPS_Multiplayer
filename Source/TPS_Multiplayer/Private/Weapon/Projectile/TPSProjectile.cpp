// (C) ToasterCat Studios 2025

#include "Weapon/Projectile/TPSProjectile.h"

#include "Character/TPSCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

ATPSProjectile::ATPSProjectile()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	SetRootComponent(CollisionComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CollisionComponent);

#if WITH_EDITORONLY_DATA
	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	if (ArrowComponent)
	{
		ArrowComponent->ArrowColor = FColor(200, 255, 200);
		ArrowComponent->bTreatAsASprite = true;
		ArrowComponent->SetupAttachment(CollisionComponent);
		ArrowComponent->bIsScreenSizeScaled = true;
		ArrowComponent->SetSimulatePhysics(false);
	}
#endif
}

void ATPSProjectile::BeginPlay()
{
	Super::BeginPlay();

	ElapsedLifetimeSeconds = 0;
}

void ATPSProjectile::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	FHitResult hitResult;
	bool isHit = DetectCollisionByLineTrace(deltaSeconds, hitResult);

	if (isHit)
	{
		AActor* hitActor = hitResult.GetActor();
		ATPSCharacter* character = Cast<ATPSCharacter>(hitActor);
		if (IsValid(character))
		{
			UE_LOG(LogTemp, Log, TEXT("Hit Character: [%s]"), *character->Name);
			CharacterHit(character, hitResult);

			if (HasAuthority())
			{
				// TODO: Apply Damage & Effects
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Hit Surface: [%s]"), *hitActor->GetHumanReadableName());
			SurfaceHit(hitActor, hitResult);
		}
	}

	ElapsedLifetimeSeconds += deltaSeconds;
	if (ElapsedLifetimeSeconds > LifetimeSeconds)
	{
		UE_LOG(LogTemp, Log, TEXT("[TTL] Projectile Destroyed"));
		Destroy();
	}
}


void ATPSProjectile::Launch()
{
	FVector forward = GetActorForwardVector() * InitialVelocity;
	CollisionComponent->SetPhysicsLinearVelocity(forward, true, "None");

	OnLaunch();
}


bool ATPSProjectile::DetectCollisionByLineTrace(const float deltaSeconds, FHitResult& outHitResult) {
	AActor* hitActor = NULL;

	FVector interpVector = GetVelocity() * deltaSeconds;

	FVector startLoc = GetActorLocation();
	FVector endLoc = startLoc + interpVector;

	ETraceTypeQuery channel = TraceTypeQuery_MAX;
	TArray<AActor*> actorsToIgnore;
	EDrawDebugTrace::Type debugTrace = EDrawDebugTrace::Type::ForDuration;

	bool isHit = false;
	if (ShowCollisionTrace)
	{
		isHit = UKismetSystemLibrary::LineTraceSingle(this, startLoc, endLoc,
			channel, false, actorsToIgnore, debugTrace,
			outHitResult,
			true,
			FLinearColor::Green, FLinearColor::Red, 1.f);
	}
	else
	{
		isHit = UKismetSystemLibrary::LineTraceSingle(this, startLoc, endLoc,
			channel, false, actorsToIgnore, debugTrace,
			outHitResult,
			true);
	}

	return isHit;
}

void ATPSProjectile::CharacterHit(ATPSCharacter* character, FHitResult hit)
{
	if (!hit.IsValidBlockingHit() || !IsValid(character)) { return; }

	OnCharacterHit(character, hit);
}


void ATPSProjectile::SurfaceHit(AActor* sceneActor, FHitResult hit)
{
	if (!hit.IsValidBlockingHit() 
		|| !IsValid(sceneActor)
		|| !IsValid(hit.GetComponent())) { return; }

	// Carry-Over Physics
	if (hit.GetComponent()->IsSimulatingPhysics())
	{
		hit.GetComponent()->AddImpulseAtLocation(CalculateImpulseJoules(), hit.Location, "None");
	}

	// TODO: Target Interface Execution

	OnSurfaceHit(sceneActor, hit);
}

FVector ATPSProjectile::CalculateImpulseJoules() const
{
	UE::Math::TVector<double> direction;
	float magnitude;
	GetVelocity().ToDirectionAndLength(direction, magnitude);

	magnitude = magnitude / 100; // convert to m/s

	// KE == v^2 * (m/2)
	float joules = (magnitude * magnitude) * CollisionComponent->GetMass();

	FVector impulseVector = joules * direction;
	return impulseVector;
}

