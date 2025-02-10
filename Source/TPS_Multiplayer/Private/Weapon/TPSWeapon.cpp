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

    CurrentAmmunitionCount = Configuration->AmmunitionCapacity;

	CurrentWeaponState = Ready;
	PreviousWeaponState = Arming;
	IsFiring = false;
	IsAiming = false;
	IsEquipped = false;
	IsReloading = false;

	HasEverFired = false;

	HasTriggerCompleted = false;
	TimeLastFired = 0;
	SuccessiveFireCount = 0;
}

void ATPSWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsFiring)
	{
		if (CanFire())
		{
			Fire();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("-<click>-"));
		}
	}
}

void ATPSWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    DOREPLIFETIME(ATPSWeapon, CurrentAmmunitionCount);
	DOREPLIFETIME(ATPSWeapon, IsReloading);
    DOREPLIFETIME(ATPSWeapon, IsAiming);
    DOREPLIFETIME(ATPSWeapon, IsFiring);
}


void ATPSWeapon::StartUse()
{
    Super::StartUse();

    IsFiring = true;
	ApplyWeaponState(Firing);
}

void ATPSWeapon::StopUse()
{
    Super::StopUse();

    IsFiring = false;
	ApplyWeaponState(PreviousWeaponState);

	// Reset Trigger
	HasTriggerCompleted = false;
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
	OnFire();

	PerformFire();

	CurrentAmmunitionCount--;
	TimeLastFired = FApp::GetGameTime();
	SuccessiveFireCount++;

	switch (Configuration->FireMode)
	{
	case SingleShot:
		HasTriggerCompleted = true;
		break;
	case Burst:
		if (SuccessiveFireCount >= Configuration->BurstFireCount)
		{
			HasTriggerCompleted = true;
		}
		break;
	case FullAuto:
	default:
		break;
	}

	if (CurrentAmmunitionCount <= 0)
	{
		HasTriggerCompleted = true;
	}

	HasEverFired = true;
}

bool ATPSWeapon::CanFire()
{
	if (HasTriggerCompleted)
	{
		return false;
	}

	float cycleRateSeconds = 1.0f / Configuration -> CycleRate;

	float currentGameTime = FApp::GetGameTime();
	if (CurrentAmmunitionCount > 0
		&& (currentGameTime - cycleRateSeconds) > TimeLastFired) {
		return true;
	}
	return false;
}


void ATPSWeapon::StartReload()
{
    ApplyWeaponState(Arming);

	if (CurrentAmmunitionCount > 0 && Configuration->HasChamber)
	{
		CurrentAmmunitionCount = 1;
	}
}

void ATPSWeapon::CommitReload(int newAmmunitionCount)
{
	CurrentAmmunitionCount += newAmmunitionCount;
	ApplyWeaponState(Ready);
}

void ATPSWeapon::ApplyWeaponState(ETPSWeaponState newState)
{
	if (newState == CurrentWeaponState) { return; }

	PreviousWeaponState = CurrentWeaponState;
	CurrentWeaponState = newState;
}
