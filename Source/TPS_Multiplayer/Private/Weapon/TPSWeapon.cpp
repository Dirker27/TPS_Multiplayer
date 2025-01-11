#include "Weapon/TPSWeapon.h"

ATPSWeapon::ATPSWeapon() {
    PrimaryActorTick.bCanEverTick = true;
}

ATPSWeapon::~ATPSWeapon() {
    // destruct
}

void ATPSWeapon::Equip()
{
    Super::Equip();
}

void ATPSWeapon::UnEquip()
{
    Super::UnEquip();
}