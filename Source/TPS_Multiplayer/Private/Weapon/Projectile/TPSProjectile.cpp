// (C) ToasterCat Studios 2025

#include "Weapon/Projectile/TPSProjectile.h"

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
