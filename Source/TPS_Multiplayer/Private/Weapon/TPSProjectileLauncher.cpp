// (C) ToasterCat Studios 2025

#include "Weapon/TPSProjectileLauncher.h"

ATPSProjectileLauncher::ATPSProjectileLauncher()
{
	Muzzle = CreateDefaultSubobject<UTPSMountPoint>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(CollisionComponent);

	ArrowComponent->SetupAttachment(Muzzle);
}

void ATPSProjectileLauncher::StartUse()
{
	Super::StartUse();

	Launch();
}

void ATPSProjectileLauncher::StopUse()
{
	Super::StartUse();
}

void ATPSProjectileLauncher::Launch()
{
	ATPSProjectile* p = GetWorld()->SpawnActor<ATPSProjectile>(ProjectileTemplate,
		Muzzle->GetComponentTransform().GetLocation(), Muzzle->GetComponentTransform().GetRotation().Rotator());
	//ATPSProjectile* p = GetWorld()->SpawnActor<ATPSProjectile>(ProjectileTemplate);

	if (IsValid(p)) {
		p->Launch();
		UE_LOG(LogTemp, Log, TEXT("YEET?"));
	}
}
