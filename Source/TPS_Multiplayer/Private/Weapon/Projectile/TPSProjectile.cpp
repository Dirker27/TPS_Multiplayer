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
			OnCharacterHit(character, hitResult);

			if (HasAuthority())
			{
				// TODO: Apply Damage & Effects
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Hit Surface: [%s]"), *hitActor->GetHumanReadableName());
			OnSurfaceHit(hitActor, hitResult);
		}
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
