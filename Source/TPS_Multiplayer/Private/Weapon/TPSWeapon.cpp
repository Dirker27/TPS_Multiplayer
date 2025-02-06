// (C) ToasterCat Studios 2025

#include "Weapon/TPSWeapon.h"

#include "Net/UnrealNetwork.h"

ATPSWeapon::ATPSWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

    Configuration = CreateDefaultSubobject<UTPSWeaponConfiguration>(TEXT("DefaultConfiguration"));
}

void ATPSWeapon::BeginPlay()
{
    Super::BeginPlay();

    CurrentAmmunition = Configuration->AmmunitionCapacity;

	IsFiring = false;
	IsAiming = false;
	IsEquipped = false;
	IsReloading = false;
	HasEverFired = false;

	CanFire = true;
	TimeLastFired = FApp::GetGameTime();
	SuccessiveFireCount = 0;
}

void ATPSWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsFiring)
	{
		float currentGameTime = FApp::GetGameTime();

		if (CanFire
			&& (currentGameTime - Configuration->FireRateDelaySeconds) > TimeLastFired
			&& CurrentAmmunition > 0)
		{
			Fire();

			switch (Configuration->FireMode)
			{
			case SingleShot:
				CanFire = false;
				break;
			case Burst:
				if (SuccessiveFireCount >= Configuration->BurstFireCount) { CanFire = false; }
				break;
			case FullAuto:
				break;
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("-<click>-"));
		}
	}
}

void ATPSWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    DOREPLIFETIME(ATPSWeapon, CurrentAmmunition);
	DOREPLIFETIME(ATPSWeapon, IsReloading);
    DOREPLIFETIME(ATPSWeapon, IsAiming);
    DOREPLIFETIME(ATPSWeapon, IsFiring);
}


void ATPSWeapon::StartUse()
{
    Super::StartUse();
    IsFiring = true;
}

void ATPSWeapon::StopUse()
{
    Super::StopUse();

    IsFiring = false;

	// Reset Trigger
	CanFire = true;
	SuccessiveFireCount = 0;
}


void ATPSWeapon::Equip()
{
    Super::Equip();
}

void ATPSWeapon::UnEquip()
{
    Super::UnEquip();
}


void ATPSWeapon::Fire()
{
	UE_LOG(LogTemp, Log, TEXT("BANG!"));

	PerformFire();

	CurrentAmmunition--;
	TimeLastFired = FApp::GetGameTime();
	SuccessiveFireCount++;

	HasEverFired = true;
}

void ATPSWeapon::Reload()
{
    // 'plus 1'
    if (CurrentAmmunition > 0)
    {
        CurrentAmmunition = Configuration->AmmunitionCapacity + 1;
    }
    else
    {
        CurrentAmmunition = Configuration->AmmunitionCapacity;
    }
}