// (C) ToasterCat Studios 2025

#include "Behavior/TPSMountPoint.h"

UTPSMountPoint::UTPSMountPoint()
{
    //SphereComponent = NewObject<USphereComponent>(this);
    //SphereComponent->SetSphereRadius(0.25f, true);
}

FVector UTPSMountPoint::GetCurrentPosition() const
{
    return GetRelativeLocation();
}

FRotator UTPSMountPoint::GetCurrentRotation() const
{
    return GetRelativeRotation();
}