// (C) ToasterCat Studios 2024

#include "Character/TPSCharacter.h"

#include <Kismet/KismetSystemLibrary.h>
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Net/UnrealNetwork.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Player/TPSPlayerState.h"

ATPSCharacter::ATPSCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	UnitFrameWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("UnitFrameWidget"));
	DebugFrameWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DebugFrameWidget"));
}

void ATPSCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPSCharacter, CurrentHealth);
	DOREPLIFETIME(ATPSCharacter, CurrentArmor);

	DOREPLIFETIME(ATPSCharacter, CurrentLocomotionState);
	DOREPLIFETIME(ATPSCharacter, CurrentCharacterState);

	DOREPLIFETIME(ATPSCharacter, MovementSpeedModifier);

	DOREPLIFETIME(ATPSCharacter, IsAiming);
	DOREPLIFETIME(ATPSCharacter, IsFiring);
	DOREPLIFETIME(ATPSCharacter, IsBoosting);
	DOREPLIFETIME(ATPSCharacter, IsCrouchInputReceived);


	//DOREPLIFETIME(ATPSCharacter, ShouldNotify);
}

void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		// Init
	}
}

void ATPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ShouldNotify) {
		NotifyDisplayWidgets.Broadcast();
		ShouldNotify = false;
	}
}

// AI Enhancement - Detection FOV is rooted to Character's HEAD.
void ATPSCharacter::GetActorEyesViewPoint(FVector& Location, FRotator& Rotation) const
{
	Location = GetMesh()->GetSocketLocation(EyeSocketName);
	Rotation = GetMesh()->GetSocketRotation(EyeSocketName);
}

// Blueprint Hook for on-fallout death animation.
void ATPSCharacter::FellOutOfWorld(const class UDamageType& dmgType) {
	OnFellOutOfWorld();
}

bool ATPSCharacter::IsAlive() const
{
	return (CurrentCharacterState != Incapacitated);
}

bool ATPSCharacter::IsCrouching() const
{
	return (CurrentLocomotionState == Crouching || CurrentLocomotionState == Prone);
}

void ATPSCharacter::ApplyLocomotionState(const ETPSLocomotionState LocomotionState)
{
	if (CurrentLocomotionState == LocomotionState) { return; } // swallow redundant state changes

	PreviousLocomotionState = CurrentLocomotionState;
	CurrentLocomotionState = LocomotionState;

	ShouldNotify = true;
}
void ATPSCharacter::RevertLocomotionState() {
	ETPSLocomotionState swap = PreviousLocomotionState;
	CurrentLocomotionState = PreviousLocomotionState;
	PreviousLocomotionState = swap;

	ShouldNotify = true;
}

void ATPSCharacter::ApplyCharacterState(const ETPSCharacterState CharacterState)
{
	if (CurrentCharacterState == CharacterState) { return; } // swallow redundant state changes

	PreviousCharacterState = CurrentCharacterState;
	CurrentCharacterState = CharacterState;

	ShouldNotify = true;
}
void ATPSCharacter::RevertCharacterState() {
	ETPSCharacterState swap = PreviousCharacterState;
	CurrentCharacterState = PreviousCharacterState;
	PreviousCharacterState = swap;

	ShouldNotify = true;
}

/**
 * https://www.notion.so/Game-Design-Document-GDD-670fda60cfeb41a089970b8fd240acaa?pvs=4#c31b4f8df636457b9783b951d60ecf03
 */
float ATPSCharacter::GetBaseSpeedForCharacterState(const ETPSCharacterState CharacterState)
{
	switch (CharacterState) {
	case Casual:
		return 200;
	case Combat:
		return 300;
	case Injured:
		return 100;
	case Incapacitated:
	default:
		return 0;
	}
}

/**
 * We actually set this with GameplayEffects. Leaving this here for legacy context
 *   and documentation link:
 * 
 * https://www.notion.so/Game-Design-Document-GDD-670fda60cfeb41a089970b8fd240acaa?pvs=4#c31b4f8df636457b9783b951d60ecf03 
 */
float ATPSCharacter::GetSpeedModifierForLocomotionState(const ETPSLocomotionState LocomotionState)
{
	switch (LocomotionState) {
	case Standing:
		return 1.0;
	case Crouching:
		return 0.5;
	case Prone:
		return 0.1;
	case Sprinting:
		return 2.0;
	case Ragdoll:
	default:
		return 0;
	}
}

float ATPSCharacter::UpdateCharacterSpeedForCurrentState()
{
	float baseSpeed = GetBaseSpeedForCharacterState(CurrentCharacterState);
	float locomotionStateModifier = GetSpeedModifierForLocomotionState(CurrentLocomotionState);

	//float modifier = MovementSpeedModifier;
	// Set by GAS
	UAbilitySystemComponent* asc = GetAbilitySystemComponent();
	if (IsValid(asc)) {
		MovementSpeedModifier = asc->GetNumericAttribute(UStandardAttributeSet::GetMovementSpeedModifierAttribute());
	}

	CurrentMaxWalkSpeed = baseSpeed * MovementSpeedModifier;

	UCharacterMovementComponent* characterMovement = GetCharacterMovement();
	characterMovement->MaxWalkSpeed = CurrentMaxWalkSpeed;
	characterMovement->MaxWalkSpeedCrouched = CurrentMaxWalkSpeed;

	// Adjusts collider to crouch height
	if (CurrentLocomotionState == Crouching) {
		Crouch();
	}
	else {
		UnCrouch();
	}

	return CurrentMaxWalkSpeed;
}



void ATPSCharacter::UpdateInputContextForCurrentState()
{
	/*player = GetPlayer()
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!InputMapping.IsNull())
			{
				InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), Priority);
			}
		}
	}*/
}


void ATPSCharacter::EvaluateStateAndApplyUpdates()
{
	UE_LOG(LogTemp, Log, TEXT("EVAL-CHARACTER"));

	SyncAttributesFromGAS();

	EvaluateLocomotionStateForCurrentInput();
	UpdateCharacterSpeedForCurrentState();
	UpdateInputContextForCurrentState();

	ShouldNotify = true;
}

void ATPSCharacter::StartAim() {
	OnAimAbilityStart();
}
void ATPSCharacter::EndAim() {
	OnAimAbilityEnd();
}

void ATPSCharacter::StartFireWeapon() {
	OnFireWeaponAbilityStart();
}
void ATPSCharacter::EndFireWeapon() {
	OnFireWeaponAbilityEnd();
}

// TODO: Make this follow a strategy pattern
ETPSLocomotionState ATPSCharacter::EvaluateLocomotionStateForCurrentInput()
{
	//- Non-Combat (restricted states) -----------------------------------=
	//
	if (CurrentCharacterState != Combat) {
		
		switch (CurrentLocomotionState) {
		case Standing:
			if (IsCrouchInputReceived) {
				ApplyLocomotionState(Crouching);
			}
			else if (IsBoosting) {
				ApplyLocomotionState(Sprinting);
			}
			break;

		case Crouching:
			if (!IsCrouchInputReceived) {
				ApplyLocomotionState(Standing);
			}
			break;

		case Prone:
			ApplyLocomotionState(Crouching);
			break;
		case Sprinting:
			if (!IsBoosting || IsActionActive()) {
				ApplyLocomotionState(Standing);
			}
			else if (IsCrouchInputReceived) {
				ApplyLocomotionState(Crouching);
			}
			break;
		default:
			ApplyLocomotionState(Standing);
			break;
		}

		return CurrentLocomotionState;
	}

	//- Combat (all states available) ---------------------------------------=
	//
	switch (CurrentLocomotionState) {
	case Standing:
		if (IsCrouchInputReceived) {
			ApplyLocomotionState(Crouching);
		}
		else if (IsBoosting) {
			ApplyLocomotionState(Sprinting);
		}
		break;

	case Crouching:
		if (!IsCrouchInputReceived) {
			ApplyLocomotionState(Standing);
		}
		break;

	case Prone:
		// STUB - just switch to Crouching for now.
		ApplyLocomotionState(Crouching);
		break;

	case Sprinting:
		if (!IsBoosting || IsActionActive()) {
			ApplyLocomotionState(Standing);
		}
		else if (IsCrouchInputReceived) {
			ApplyLocomotionState(Crouching);
		}
		break;

	default:
		ApplyLocomotionState(Standing);
		break;
	}

	return CurrentLocomotionState;
}

bool ATPSCharacter::IsActionActive() const {
	return IsAiming || IsFiring;
}


AActor* ATPSCharacter::LineTrace(const UObject* WorldContextObject) {
	AActor* hitActor = NULL;

	FVector startLoc = GetActorLocation();

	FVector forward = GetActorForwardVector();
	FVector endLoc = startLoc + (forward * 1000.f);

	ETraceTypeQuery channel = TraceTypeQuery_MAX;
	TArray<AActor*> actorsToIgnore;
	EDrawDebugTrace::Type debugTrace = EDrawDebugTrace::Type::ForOneFrame;
	FHitResult hitResult;

	bool isHit = UKismetSystemLibrary::LineTraceSingle(WorldContextObject, startLoc, endLoc,
		channel, false, actorsToIgnore, debugTrace,
		hitResult,
		true,
		FLinearColor::Red, FLinearColor::Green, 5.f);

	if (isHit) {
		hitActor = hitResult.GetActor();
	}

	return hitActor;
}



//~ ============================================================= ~//
//  ABILITY SYSTEM
//~ ============================================================= ~//


// Overridden in AI Character and Player Character to return appropriate ASC
UAbilitySystemComponent* ATPSCharacter::GetAbilitySystemComponent() const {
	return nullptr;
}

// Should only be called from SERVER when initializing.
void ATPSCharacter::SetupInitialAbilitiesAndEffects() {
	UAbilitySystemComponent* asc = GetAbilitySystemComponent();
	if (! IsValid(asc)) {
		return;
	}

	if (IsValid(InitialAbilitySet)) {
		InitiallyGrantedAbilitySpecHandles.Append(
			InitialAbilitySet->GrantAbilitiesToAbilitySystem(asc));
	}

	if (IsValid(InitialGameplayEffect)) {
		asc->ApplyGameplayEffectToSelf(
			InitialGameplayEffect->GetDefaultObject<UGameplayEffect>(),
			0,
			asc->MakeEffectContext());
	}

	asc->GetGameplayAttributeValueChangeDelegate(UCharacterHealthAttributeSet::GetArmorAttribute())
		.AddUObject(this, &ThisClass::OnArmorAttributeChanged);
	asc->GetGameplayAttributeValueChangeDelegate(UCharacterHealthAttributeSet::GetHealthAttribute())
		.AddUObject(this, &ThisClass::OnHealthAttributeChanged);
	asc->GetGameplayAttributeValueChangeDelegate(UStandardAttributeSet::GetMovementSpeedModifierAttribute())
		.AddUObject(this, &ThisClass::OnMovementAttributeChanged);
}

void ATPSCharacter::OnArmorAttributeChanged(const FOnAttributeChangeData& data) {
	UE_LOG(LogTemp, Log, TEXT("OnArmorChange"));
	ShouldNotify = true;

	//CurrentArmor = data.NewValue;
}
void ATPSCharacter::OnHealthAttributeChanged(const FOnAttributeChangeData& data) {
	UE_LOG(LogTemp, Log, TEXT("OnHealthChange"));
	ShouldNotify = true;

	//CurrentHealth = data.NewValue;
}
void ATPSCharacter::OnMovementAttributeChanged(const FOnAttributeChangeData& data) {
	UE_LOG(LogTemp, Log, TEXT("OnMovementChange"));
	ShouldNotify = true;

	//MovementSpeedModifier = data.NewValue;
}

void ATPSCharacter::SyncAttributesFromGAS() {
	UAbilitySystemComponent* asc = GetAbilitySystemComponent();
	if (!IsValid(asc)) {
		return;
	}

	CurrentHealth = asc->GetNumericAttribute(UCharacterHealthAttributeSet::GetHealthAttribute());
	MaxHealth = asc->GetNumericAttribute(UCharacterHealthAttributeSet::GetHealthMaxAttribute());

	CurrentArmor = asc->GetNumericAttribute(UCharacterHealthAttributeSet::GetArmorAttribute());
	MaxArmor = asc->GetNumericAttribute(UCharacterHealthAttributeSet::GetArmorMaxAttribute());

	MovementSpeedModifier = asc->GetNumericAttribute(UStandardAttributeSet::GetMovementSpeedModifierAttribute());

	ShouldNotify = true;
}
