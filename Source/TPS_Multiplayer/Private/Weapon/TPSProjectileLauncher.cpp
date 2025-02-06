// (C) ToasterCat Studios 2025

#include "Weapon/TPSProjectileLauncher.h"

ATPSProjectileLauncher::ATPSProjectileLauncher()
{
	Muzzle = CreateDefaultSubobject<UTPSMountPoint>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(CollisionComponent);

	#if WITH_EDITORONLY_DATA
	ArrowComponent->SetupAttachment(Muzzle);
	#endif
}

void ATPSProjectileLauncher::StartUse()
{
	Super::StartUse();
}

void ATPSProjectileLauncher::StopUse()
{
	Super::StopUse();
}

void ATPSProjectileLauncher::PerformFire()
{
	//if (HasAuthority()) {
		LaunchProjectile();
	//}
}	

void ATPSProjectileLauncher::LaunchProjectile()
{
	ATPSProjectile* p = GetWorld()->SpawnActor<ATPSProjectile>(ProjectileTemplate,
		Muzzle->GetComponentTransform().GetLocation(), Muzzle->GetComponentTransform().GetRotation().Rotator());
	//ATPSProjectile* p = GetWorld()->SpawnActor<ATPSProjectile>(ProjectileTemplate);

	if (IsValid(p)) {
		p->Launch();
		UE_LOG(LogTemp, Log, TEXT("YEET?"));
	}
}
