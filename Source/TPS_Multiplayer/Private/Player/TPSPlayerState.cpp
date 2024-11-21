// (C) ToasterCat Studios 2024

#include "Player/TPSPlayerState.h"

ATPSPlayerState::ATPSPlayerState() {
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	StandardAttributes = CreateDefaultSubobject<UStandardAttributeSet>(TEXT("StandardAttributes"));
	CharacterHealthAttributes = CreateDefaultSubobject<UCharacterHealthAttributeSet>(TEXT("HealthAttributes"));
	WeaponAttributes = CreateDefaultSubobject<UWeaponAttributeSet>(TEXT("WeaponAttributes"));

	NetUpdateFrequency = 30.0f;
}

ATPSPlayerState::~ATPSPlayerState() {
	// destruct
}

void ATPSPlayerState::BeginPlay() {
	Super::BeginPlay();
}

UAbilitySystemComponent* ATPSPlayerState::GetAbilitySystemComponent() const {
	return AbilitySystemComponent;
}


