#include "Inventory/TPSEquipableItem.h"

/*ATPSEquipableItem::ATPSEquipableItem() {
	//Super();
    PrimaryActorTick.bCanEverTick = true;
}
ATPSEquipableItem::~ATPSEquipableItem() {
    // destruct
}*/

void ATPSEquipableItem::Equip()
{
	OnEquip();
}
void ATPSEquipableItem::UnEquip()
{
	OnUnEquip();
}

void ATPSEquipableItem::StartUse()
{
	OnStartUse();
}
void ATPSEquipableItem::StopUse()
{
	OnStopUse();
}
