// (C) ToasterCat Studios 2025

#include "Weapon/TPSWeapon.h"

#include "Net/UnrealNetwork.h"

ATPSWeapon::ATPSWeapon()
{
    Configuration = CreateDefaultSubobject<UTPSWeaponConfiguration>(TEXT("CustomConfiguration"));
}

void ATPSWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    DOREPLIFETIME(ATPSWeapon, IsAiming);
    DOREPLIFETIME(ATPSWeapon, IsFiring);
    DOREPLIFETIME(ATPSWeapon, IsArmed);
}


void ATPSWeapon::Equip()
{
    Super::Equip();

    IsArmed = true;
}

void ATPSWeapon::UnEquip()
{
    Super::UnEquip();

    IsArmed = false;
}