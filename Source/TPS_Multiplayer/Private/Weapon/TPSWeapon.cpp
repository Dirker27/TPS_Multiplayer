// (C) ToasterCat Studios 2025

#include "Weapon/TPSWeapon.h"

#include "Net/UnrealNetwork.h"

ATPSWeapon::ATPSWeapon()
{
    Configuration = CreateDefaultSubobject<UTPSWeaponConfiguration>(TEXT("CustomConfiguration"));
}

void ATPSWeapon::BeginPlay()
{
    Super::BeginPlay();

    CurrentAmmunition = Configuration->AmmunitionCapacity;
}

void ATPSWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    DOREPLIFETIME(ATPSWeapon, CurrentAmmunition);
    DOREPLIFETIME(ATPSWeapon, IsAiming);
    DOREPLIFETIME(ATPSWeapon, IsFiring);
}


void ATPSWeapon::Equip()
{
    Super::Equip();
}

void ATPSWeapon::UnEquip()
{
    Super::UnEquip();
}