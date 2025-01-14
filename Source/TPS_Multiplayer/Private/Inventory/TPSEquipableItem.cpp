#include "Inventory/TPSEquipableItem.h"

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
