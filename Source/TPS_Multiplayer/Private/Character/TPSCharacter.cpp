// (C) ToasterCat Studios 2025

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

	Inventory = CreateDefaultSubobject<UTPSCharacterInventory>(TEXT("Inventory"));

	EquipmentManager = CreateDefaultSubobject<UTPSEquipmentManager>(TEXT("EquipmentManager"));
	EquipmentManager->BindToMesh(GetMesh());

	/*EquipmentManager->PrimaryWeaponHand = CreateDefaultSubobject<UTPSMountPoint>(TEXT("EM-PrimaryWeaponHand"));
	EquipmentManager->SecondaryWeaponHand = CreateDefaultSubobject<UTPSMountPoint>(TEXT("EM-SecondaryWeaponHand"));
	EquipmentManager->BackHolster = CreateDefaultSubobject<UTPSMountPoint>(TEXT("EM-BackHolster"));
	EquipmentManager->LeftHipHolster = CreateDefaultSubobject<UTPSMountPoint>(TEXT("EM-LeftHipHolster"));
	EquipmentManager->LeftLegHolster = CreateDefaultSubobject<UTPSMountPoint>(TEXT("EM-LeftLegHolster"));
	EquipmentManager->RightHipHolster = CreateDefaultSubobject<UTPSMountPoint>(TEXT("EM-RightHipHolster"));
	EquipmentManager->RightLegHolster = CreateDefaultSubobject<UTPSMountPoint>(TEXT("EM-RightLegHolster"));*/

	/*EquipmentManager->PrimaryWeaponHand->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hand_r"));
	EquipmentManager->SecondaryWeaponHand->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hand_l"));
	EquipmentManager->BackHolster->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("spine_05"));
	EquipmentManager->LeftHipHolster->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("thigh_l"));
	EquipmentManager->LeftLegHolster->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("calf_l"));
	EquipmentManager->RightHipHolster->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("thigh_r"));
	EquipmentManager->RightLegHolster->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("calf_r"));*/


	/*EquipmentManager->PrimaryWeaponHand->TargetParentComponent = GetMesh();
	EquipmentManager->PrimaryWeaponHand->TargetSocketName = FName(TEXT("hand_r"));
	EquipmentManager->SecondaryWeaponHand->TargetParentComponent = GetMesh();
	EquipmentManager->SecondaryWeaponHand->TargetSocketName = FName(TEXT("hand_l"));
	EquipmentManager->BackHolster->TargetParentComponent = GetMesh();
	EquipmentManager->BackHolster->TargetSocketName = FName(TEXT("spine_05"));
	EquipmentManager->LeftHipHolster->TargetParentComponent = GetMesh();
	EquipmentManager->LeftHipHolster->TargetSocketName = FName(TEXT("thigh_l"));
	EquipmentManager->LeftLegHolster->TargetParentComponent = GetMesh();
	EquipmentManager->LeftLegHolster->TargetSocketName = FName(TEXT("calf_l"));
	EquipmentManager->RightHipHolster->TargetParentComponent = GetMesh();
	EquipmentManager->RightHipHolster->TargetSocketName = FName(TEXT("thigh_r"));
	EquipmentManager->RightLegHolster->TargetParentComponent = GetMesh();
	EquipmentManager->RightLegHolster->TargetSocketName = FName(TEXT("calf_r"));*/



	//UnitFrameWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("UnitFrameWidget"));
	//DebugFrameWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DebugFrameWidget"));

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
	DOREPLIFETIME(ATPSCharacter, IsInteracting);
	DOREPLIFETIME(ATPSCharacter, IsInMenu);
}

void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*EquipmentManager->PrimaryWeaponHand->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hand_r"));
	EquipmentManager->SecondaryWeaponHand->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hand_l"));
	EquipmentManager->BackHolster->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("spine_05"));
	EquipmentManager->LeftHipHolster->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("thigh_l"));
	EquipmentManager->LeftLegHolster->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("calf_l"));
	EquipmentManager->RightHipHolster->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("thigh_r"));
	EquipmentManager->RightLegHolster->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("calf_r"));*/
	
	if (HasAuthority())
	{
		// Init
	}
}

void ATPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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


// TODO: DEPRECATED! DELETEME!
void ATPSCharacter::EvaluateStateAndApplyUpdates()
{
	UE_LOG(LogTemp, Log, TEXT("EVAL-CHARACTER"));

	EvaluateLocomotionStateForCurrentInput();
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
	return IsAiming || IsFiring || IsInteracting || IsInMenu;
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
	ShouldNotify = true;
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
