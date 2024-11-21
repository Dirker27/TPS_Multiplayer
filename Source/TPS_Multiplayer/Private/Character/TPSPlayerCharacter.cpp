#include "Character/TPSPlayerCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Player/TPSPlayerState.h"

ATPSPlayerCharacter::ATPSPlayerCharacter() {
    PrimaryActorTick.bCanEverTick = true;
}

ATPSPlayerCharacter::~ATPSPlayerCharacter() {
    // destruct
}

UAbilitySystemComponent* ATPSPlayerCharacter::GetAbilitySystemComponent() const {
	if (ATPSPlayerState* ps = GetPlayerState<ATPSPlayerState>()) {
		return ps->GetAbilitySystemComponent();
	}
	return nullptr;
}

// Ability System Wiring (from TPSPlayerController)
void ATPSPlayerCharacter::InitPlayer() {
	if (ATPSPlayerState* ps = GetPlayerState<ATPSPlayerState>()) {
		ps->GetAbilitySystemComponent()->InitAbilityActorInfo(ps, this);
	}

	if (HasAuthority() || IsLocallyControlled()) {
		// init
	}
}
void ATPSPlayerCharacter::PossessedBy(AController* NewController) { // server
	Super::PossessedBy(NewController);
	InitPlayer();
}
void ATPSPlayerCharacter::OnRep_PlayerState() { // client
	Super::OnRep_PlayerState();
	InitPlayer();
}



// Called to bind functionality to input
void ATPSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);

	if (UEnhancedInputComponent* playerEnhancedInputComponent = Cast<UEnhancedInputComponent>(playerInputComponent)) {
		for (const FAbilityInputToInputActionBinding& binding : AbilityInputBindings.Bindings)
		{
			playerEnhancedInputComponent->BindAction(binding.InputAction, ETriggerEvent::Started, this, &ThisClass::AbilityInputBindingPressedHandler, binding.AbilityInput);
			playerEnhancedInputComponent->BindAction(binding.InputAction, ETriggerEvent::Completed, this, &ThisClass::AbilityInputBindingReleasedHandler, binding.AbilityInput);
		}
	}
}




// EnhancedInput -> GAS plumbing
void ATPSPlayerCharacter::AbilityInputBindingPressedHandler(EAbilityInput abilityInput) {
	UE_LOG(LogTemp, Log, TEXT("OnInput[%i]"), abilityInput);
	if (ATPSPlayerState* ps = GetPlayerState<ATPSPlayerState>()) {
		ps->GetAbilitySystemComponent()->AbilityLocalInputPressed(static_cast<uint32>(abilityInput));
	}
}
void ATPSPlayerCharacter::AbilityInputBindingReleasedHandler(EAbilityInput abilityInput) {
	UE_LOG(LogTemp, Log, TEXT("OnInput[%i]"), abilityInput);
	if (ATPSPlayerState* ps = GetPlayerState<ATPSPlayerState>()) {
		ps->GetAbilitySystemComponent()->AbilityLocalInputReleased(static_cast<uint32>(abilityInput));
	}
}