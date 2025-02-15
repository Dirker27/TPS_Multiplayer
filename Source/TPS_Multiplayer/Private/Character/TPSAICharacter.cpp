#include "Character/TPSAICharacter.h"

ATPSAICharacter::ATPSAICharacter() {
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	StandardAttributes = CreateDefaultSubobject<UStandardAttributeSet>(TEXT("StandardAttributes"));
	CharacterHealthAttributes = CreateDefaultSubobject<UCharacterHealthAttributeSet>(TEXT("HealthAttributes"));
	WeaponAttributes = CreateDefaultSubobject<UWeaponAttributeSet>(TEXT("WeaponAttributes"));
}

void ATPSAICharacter::BeginPlay() {
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

UAbilitySystemComponent* ATPSAICharacter::GetAbilitySystemComponent() const {
	return AbilitySystemComponent;
}