// (C) ToasterCat Studios 2025

#include "Character/TPSCharacter.h"

#include <Kismet/KismetSystemLibrary.h>
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Net/UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Player/TPSPlayerState.h"

ATPSCharacter::ATPSCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	Configuration = CreateDefaultSubobject<UTPSCharacterConfiguration>(TEXT("DefaultConfiguration"));

	Inventory = CreateDefaultSubobject<UTPSCharacterInventory>(TEXT("Inventory"));

	EquipmentManager = CreateDefaultSubobject<UTPSEquipmentManager>(TEXT("EquipmentManager"));
	EquipmentManager->BindToMesh(GetMesh());

	//- Default Values ------------------------------------=
	//
	// Used for testing and default values.
	//   Will be overridden in Blueprints or in BeginPlay()
	//
	CurrentHealth = 100;
	MaxHealth = 100;
	CurrentArmor = 100;
	MaxArmor = 100;
	//
	MovementSpeedModifier = 1.0;
	CurrentMaxWalkSpeed = 200;
	//
	CurrentCharacterState = Casual;
	PreviousCharacterState = Incapacitated;
	CurrentLocomotionState = Standing;
	PreviousLocomotionState = Crouching;
	//
	IsBoosting = false;
	IsCrouchInputReceived = false;
	IsAiming = false;
	IsFiring = false;
	IsInteracting = false;
	IsInMenu = false;
	TargetLookRotation = FRotator::ZeroRotator;
}

void ATPSCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPSCharacter, CurrentHealth);
	DOREPLIFETIME(ATPSCharacter, CurrentArmor);

	DOREPLIFETIME(ATPSCharacter, CurrentLocomotionState);
	DOREPLIFETIME(ATPSCharacter, CurrentCharacterState);

	DOREPLIFETIME(ATPSCharacter, MovementSpeedModifier);

	DOREPLIFETIME(ATPSCharacter, IsBoosting);
	DOREPLIFETIME(ATPSCharacter, IsCrouchInputReceived);
	DOREPLIFETIME(ATPSCharacter, IsAiming);
	DOREPLIFETIME(ATPSCharacter, IsFiring);
	DOREPLIFETIME(ATPSCharacter, IsEquipping);
	DOREPLIFETIME(ATPSCharacter, IsReloading);
	DOREPLIFETIME(ATPSCharacter, IsInteracting);
	DOREPLIFETIME(ATPSCharacter, IsInMenu);

	DOREPLIFETIME(ATPSCharacter, TargetLookRotation);
}

void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		// Init
		EquipmentManager->Initialize();
	}
}

void ATPSCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	SyncAttributesFromGAS();

	ETPSLocomotionState evaluatedState = EvaluateLocomotionStateForCurrentInput();
	if (evaluatedState != CurrentLocomotionState)
	{
		ApplyLocomotionState(evaluatedState);
	}
	SyncComponentsFromState();

	if (ShouldNotify) {
		NotifyDisplayWidgets.Broadcast();
		ShouldNotify = false;
	}

	if (HasAuthority()) {
		TargetLookRotation = GetViewRotation();
	}

	ATPSWeapon* weapon = GetEquippedWeapon();
	if (IsValid(weapon))
	{
		weapon->TargetDirection = TargetLookRotation;
	}
}

void ATPSCharacter::SyncComponentsFromState()
{
	UpdateCharacterSpeedForCurrentState();
	UpdateInputContextForCurrentState();
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
bool ATPSCharacter::IsIdle() const
{
	// TODO: Determine what "Idle" means.
	return false;
}

ATPSWeapon* ATPSCharacter::GetEquippedWeapon() const
{
	if (EquipmentManager->ActiveEquipmentSlot == None) { return nullptr; }

	return Cast<ATPSWeapon>(EquipmentManager->GetItemFromEquipmentSlot(EquipmentManager->ActiveEquipmentSlot));
}

//~ ============================================================= ~//
//  BEHAVIOR OPERATIONS
//~ ============================================================= ~//

void ATPSCharacter::ApplyLocomotionState(const ETPSLocomotionState LocomotionState)
{
	if (CurrentLocomotionState == LocomotionState) { return; } // swallow redundant state changes

	PreviousLocomotionState = CurrentLocomotionState;
	CurrentLocomotionState = LocomotionState;

	// Cascade to inner components (adjusts collider height)
	if (CurrentLocomotionState == Crouching) {
		Crouch();
	}
	else if (PreviousLocomotionState == Crouching)
	{
		UnCrouch();
	}

	ShouldNotify = true;
}
void ATPSCharacter::RevertLocomotionState() {
	ApplyLocomotionState(PreviousLocomotionState);
}

void ATPSCharacter::ApplyCharacterState(const ETPSCharacterState CharacterState)
{
	if (CurrentCharacterState == CharacterState) { return; } // swallow redundant state changes

	PreviousCharacterState = CurrentCharacterState;
	CurrentCharacterState = CharacterState;

	if (CurrentCharacterState == Combat)
	{
		EquipmentManager->Ready();
	}
	else if (PreviousCharacterState == Combat)
	{
		EquipmentManager->UnReady();
	}

	ShouldNotify = true;
}
void ATPSCharacter::RevertCharacterState() {
	ApplyCharacterState(PreviousCharacterState);
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

	// TODO: Lerp accel/decell?

	UCharacterMovementComponent* characterMovement = GetCharacterMovement();
	characterMovement->MaxWalkSpeed = CurrentMaxWalkSpeed;
	characterMovement->MaxWalkSpeedCrouched = CurrentMaxWalkSpeed;

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


// TODO: Make this follow a strategy pattern baed on current CharacterState
ETPSLocomotionState ATPSCharacter::EvaluateLocomotionStateForCurrentInput()
{
	// TODO: Transitions based on allowed LocomotionStates for CharacterState

	// Character State Overrides
	if (CurrentCharacterState == Incapacitated)
	{
		return Ragdoll;
	}

	// Simplified State Tree (Casual & Combat)
	if (IsCrouchInputReceived)
	{
		return Crouching;
	}
	if (IsBoosting && !IsActionActive())
	{
		return Sprinting;
	}

	return Standing;
}

bool ATPSCharacter::IsActionActive() const {
	return IsAiming
		|| IsFiring
		|| IsEquipping
		|| IsReloading
		|| IsInteracting
		|| IsInMenu;
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
//  Ability Extensions
//~ ============================================================= ~//

// - BOOST -//

void ATPSCharacter::StartBoost() {
	IsBoosting = true;
	OnBoostAbilityStart();
}
void ATPSCharacter::EndBoost() {
	IsBoosting = false;
	OnBoostAbilityEnd();
}

// - AIM -//

void ATPSCharacter::StartAim() {
	IsAiming = true;

	ATPSWeapon* weapon = GetEquippedWeapon();
	if (weapon != nullptr)
	{
		weapon->IsAiming = true;
	}

	OnAimAbilityStart();
}
void ATPSCharacter::EndAim() {
	IsAiming = false;

	ATPSWeapon* weapon = GetEquippedWeapon();
	if (weapon != nullptr)
	{
		weapon->IsAiming = false;
	}

	OnAimAbilityEnd();
}

// - FIRE WEAPON / USE EQUIPMENT -//

void ATPSCharacter::StartFireWeapon() {
	IsFiring = true;

	ATPSWeapon* weapon = GetEquippedWeapon();
	if (weapon != nullptr)
	{
		weapon->StartUse();
	}

	OnFireWeaponAbilityStart();
}
void ATPSCharacter::EndFireWeapon() {
	IsFiring = false;

	ATPSWeapon* weapon = GetEquippedWeapon();
	if (weapon != nullptr)
	{
		weapon->StopUse();
	}

	OnFireWeaponAbilityEnd();
}

// - EQUIP WEAPON -//

void ATPSCharacter::StartEquipWeapon() {
	IsEquipping = true;

	// Temporary - derives behavior from equipment state
	if (CurrentCharacterState != Combat)
	{
		ApplyCharacterState(Combat);
	}

	OnEquipWeaponAbilityStart();
}
void ATPSCharacter::EndEquipWeapon() {
	IsEquipping = false;
	OnEquipWeaponAbilityEnd();
}

// - UN-EQUIP WEAPON -//

void ATPSCharacter::StartUnEquipWeapon() {
	IsEquipping = true;

	// Temporary - derives behavior from equipment state
	if (CurrentCharacterState != Casual)
	{
		ApplyCharacterState(Casual);
	}

	OnUnEquipWeaponAbilityStart();
}
void ATPSCharacter::EndUnEquipWeapon() {
	IsEquipping = false;
	OnUnEquipWeaponAbilityEnd();
}

// - RELOAD WEAPON -//

void ATPSCharacter::StartReloadWeapon() {
	IsReloading = true;

	ATPSWeapon* weapon = GetEquippedWeapon();
	if (weapon != nullptr)
	{
		weapon->StartReload();
	}

	OnReloadWeaponAbilityStart();
}
void ATPSCharacter::EndReloadWeapon() {
	IsReloading = false;

	ATPSWeapon* weapon = GetEquippedWeapon();
	if (weapon != nullptr)
	{
		weapon->CommitReload(weapon->Configuration->AmmunitionCapacity);
	}

	OnReloadWeaponAbilityEnd();
}

// - INTERACT -//

void ATPSCharacter::StartInteract() {
	IsInteracting = true;
	OnInteractAbilityStart();
}
void ATPSCharacter::EndInteract() {
	IsInteracting = false;
	OnInteractAbilityEnd();
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

	CurrentArmor = data.NewValue;
	ShouldNotify = true;
}
void ATPSCharacter::OnHealthAttributeChanged(const FOnAttributeChangeData& data) {
	UE_LOG(LogTemp, Log, TEXT("OnHealthChange"));

	CurrentHealth = data.NewValue;
	ShouldNotify = true;
}
void ATPSCharacter::OnMovementAttributeChanged(const FOnAttributeChangeData& data) {
	if (HasAuthority()) {
		UE_LOG(LogTemp, Log, TEXT("OnMovementChange-Server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("OnMovementChange-Client"));
	}

	MovementSpeedModifier = data.NewValue;
	//ShouldNotify = true;
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
}

//~ ============================================================= ~//
//  END
//~ ============================================================= ~//