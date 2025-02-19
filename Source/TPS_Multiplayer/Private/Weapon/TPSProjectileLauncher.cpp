// (C) ToasterCat Studios 2025

#include "Weapon/TPSProjectileLauncher.h"

#include "Kismet/KismetMathLibrary.h"
#include "Util/TPSFunctionLibrary.h"

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
	if (HasAuthority()) {
		// Adjust the shooter's aim.
		FRotator adjustedDirection = TargetDirection;
		FVector2D noise = CalculateAccuracyNoise();
		adjustedDirection.Add(noise.X, noise.Y, 0);

		FVector debugVector = adjustedDirection.Vector() * 200;
		UTPSFunctionLibrary::DrawDebugTrace(this, Muzzle->GetComponentTransform().GetLocation(), debugVector,
			FLinearColor::Yellow, FLinearColor::Yellow, 2.f);


		int projectileCount = 1;
		if (Configuration->ProjectileBehavior == Spread)
		{
			projectileCount = Configuration->SpreadCount;
		}
		for (int i = 0; i < projectileCount; i++)
		{
			// Adjust the weapon's spread.
			FRotator spreadDirection = adjustedDirection;
			noise = CalculateSpreadNoise();
			spreadDirection.Add(noise.X, noise.Y, 0);

			debugVector = spreadDirection.Vector() * 100;
			UTPSFunctionLibrary::DrawDebugTrace(this, Muzzle->GetComponentTransform().GetLocation(), debugVector,
				FLinearColor::Blue, FLinearColor::Blue, 2.f);
			
			LaunchProjectile(spreadDirection);
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


FVector2D ATPSProjectileLauncher::CalculateAccuracyNoise()
{
	// Apply MOA Noise (independent of character's accuracy, this is just the Weapon's spread)
	float deltaPitch = UKismetMathLibrary::RandomIntegerInRange(-1 * TargetAccuracyTolerance.X, TargetAccuracyTolerance.X);
	float deltaYaw = UKismetMathLibrary::RandomIntegerInRange(-1 * TargetAccuracyTolerance.Y, TargetAccuracyTolerance.Y);

	return FVector2D(deltaPitch, deltaYaw);
}

// Apply MOA Noise (independent of character's accuracy, this is just the Weapon's spread)
FVector2D ATPSProjectileLauncher::CalculateSpreadNoise()
{
	// MOA == "Minute of Angle" -> 1/60 of a 360-degree.
	//  1 MOA ~= 1 inch @ 100 yards
	float pitchDegrees;
	float yawDegrees;
	if (Configuration->SpreadMode == MOA) {
		pitchDegrees = Configuration->SpreadMOA / 60.f;
		yawDegrees = Configuration->SpreadMOA / 60.f;
	}
	else
	{
		pitchDegrees = Configuration->SpreadDegrees.X;
		yawDegrees = Configuration->SpreadDegrees.Y;
	}

	//float deltaPitch = UKismetMathLibrary::RandomFloatInRange(-1 * pitchDegrees, pitchDegrees);
	//float deltaYaw = UKismetMathLibrary::RandomFloatInRange(-1 * yawDegrees, yawDegrees);
	//return FVector2D(deltaPitch, deltaYaw);


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
