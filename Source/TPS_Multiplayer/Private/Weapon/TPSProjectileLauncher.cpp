// (C) ToasterCat Studios 2025

#include "Weapon/TPSProjectileLauncher.h"

#include "Kismet/KismetMathLibrary.h"

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

void ATPSProjectileLauncher::PerformFire(FRotator targetDirection)
{
	if (HasAuthority()) {

		int projectileCount = 1;
		if (ProjectileBehavior == Spread)
		{
			projectileCount = SpreadCount;
		}

		for (int i = 0; i < projectileCount; i++)
		{
			// Apply MOA Noise (independent of character's accuracy, this is just the Weapon's spread)
			FRotator adjustedDirection = targetDirection;
			float deltaYaw = UKismetMathLibrary::RandomIntegerInRange(-1 * Configuration->AccuracySpreadMOA, Configuration->AccuracySpreadMOA);
			float deltaPitch = UKismetMathLibrary::RandomIntegerInRange(-1 * Configuration->AccuracySpreadMOA, Configuration->AccuracySpreadMOA);
			adjustedDirection.Add(deltaPitch, deltaYaw, 0);
			LaunchProjectile(adjustedDirection);
		}
	}
}

// TODO: This should be a MultiCast RPC for replication.
void ATPSProjectileLauncher::LaunchProjectile(FRotator targetDirection)
{
	ATPSProjectile* p = GetWorld()->SpawnActor<ATPSProjectile>(ProjectileTemplate,
		Muzzle->GetComponentTransform().GetLocation(), targetDirection);

	p->SetReplicates(true);
	p->SetReplicateMovement(true);

	if (IsValid(p)) {
		p->Launch();
		//UE_LOG(LogTemp, Log, TEXT("YEET?"));
	}
}
