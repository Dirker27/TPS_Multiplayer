// (C) ToasterCat Studios 2025

#include "Behavior/TPSMountPoint.h"

UTPSMountPoint::UTPSMountPoint()
{
    //SphereComponent = CreateDefaultSubobject<USphereComponent>(TargetSocketName);
    //SphereComponent->SetSphereRadius(.1f, true);
    //SphereComponent->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("")));
}

FVector UTPSMountPoint::GetCurrentPosition() const
{
    return FVector::Zero();
}

FVector UTPSMountPoint::GetCurrentEulerRotation() const
{
    return FVector::Zero();
}