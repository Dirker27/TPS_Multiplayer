// (C) ToasterCat Studios 2024

#include "Character/TPSCharacter.h"

#include <Kismet/KismetSystemLibrary.h>
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
ATPSCharacter::ATPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	StandardAttributes = CreateDefaultSubobject<UStandardAttributeSet>(TEXT("StandardAttributeSet"));
}

// Called when the game starts or when spawned
void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		SetupInitialAbilitiesAndEffects();
	}
}

// Called every frame
void ATPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GetCharacterMovement()->Set
}

// Called to bind functionality to input
void ATPSCharacter::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);

	if (UEnhancedInputComponent* playerEnhancedInputComponent = Cast<UEnhancedInputComponent>(playerInputComponent)) {
		for (const FAbilityInputToInputActionBinding& binding : AbilityInputBindings.Bindings)
		{
			//playerEnhancedInputComponent->BindAction(binding.InputAction, ETriggerEvent::Triggered, this, &ThisClass::AbilityInputBindingPressedHandler, binding.AbilityInput);
			playerEnhancedInputComponent->BindAction(binding.InputAction, ETriggerEvent::Started, this, &ThisClass::AbilityInputBindingPressedHandler, binding.AbilityInput);
			
			playerEnhancedInputComponent->BindAction(binding.InputAction, ETriggerEvent::Completed, this, &ThisClass::AbilityInputBindingReleasedHandler, binding.AbilityInput);
			//playerEnhancedInputComponent->BindAction(binding.InputAction, ETriggerEvent::Canceled, this, &ThisClass::AbilityInputBindingReleasedHandler, binding.AbilityInput);
		}
	}
}

// EnhancedInput -> GAS plumbing
void ATPSCharacter::AbilityInputBindingPressedHandler(EAbilityInput abilityInput) {
	//UE_LOG(LogTemp, Log, TEXT("OnInputPressed[%i]"), abilityInput);
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<uint32>(abilityInput));
}
void ATPSCharacter::AbilityInputBindingReleasedHandler(EAbilityInput abilityInput) {
	//UE_LOG(LogTemp, Log, TEXT("OnInputReleased[%i]"), abilityInput);
	AbilitySystemComponent->AbilityLocalInputReleased(static_cast<uint32>(abilityInput));
}

void ATPSCharacter::GetActorEyesViewPoint(FVector& Location, FRotator& Rotation) const
{
	Location = GetMesh()->GetSocketLocation(EyeSocketName);
	Rotation = GetMesh()->GetSocketRotation(EyeSocketName);
}

void ATPSCharacter::FellOutOfWorld(const class UDamageType& dmgType) {
	OnFellOutOfWorld();
}

bool ATPSCharacter::IsCrouching() const
{
	return (CurrentLocomotionState == Crouching || CurrentLocomotionState == Prone);
}

void ATPSCharacter::ApplyLocomotionState(const ETPSLocomotionState LocomotionState)
{
	PreviousLocomotionState = CurrentLocomotionState;
	CurrentLocomotionState = LocomotionState;
}

void ATPSCharacter::ApplyCharacterState(const ETPSCharacterState CharacterState)
{
	PreviousCharacterState = CurrentCharacterState;
	CurrentCharacterState = CharacterState;
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

	CurrentMaxWalkSpeed = baseSpeed * locomotionStateModifier;

	// TODO: Apply to CharacterMovement

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


void ATPSCharacter::ApplyCharacterAttributesForCurrentState()
{
	UpdateCharacterSpeedForCurrentState();
	UpdateInputContextForCurrentState();	
}


// TODO: Make this follow a state-driven design pattern
ETPSLocomotionState ATPSCharacter::EvaluateLocomotionStateForCurrentInput()
{
	//- Non-Combat (restricted states) -----------------------------------=
	//
	if (CurrentCharacterState != Combat) {
		
		switch (CurrentLocomotionState) {
		case Standing:
			if (isCrouchInputReceived) {
				ApplyLocomotionState(Crouching);
			}
			else if (isBoosting) {
				ApplyLocomotionState(Sprinting);
			}
			break;

		case Crouching:
			if (!isCrouchInputReceived) {
				ApplyLocomotionState(Standing);
			}
			break;

		case Prone:
			ApplyLocomotionState(Crouching);
			break;
		case Sprinting:
			if (!isBoosting || IsActionActive()) {
				ApplyLocomotionState(Standing);
			}
			else if (isCrouchInputReceived) {
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
		if (isCrouchInputReceived) {
			ApplyLocomotionState(Crouching);
		}
		else if (isProneInputReceived) {
			ApplyLocomotionState(Prone);
		}
		else if (isBoosting) {
			ApplyLocomotionState(Sprinting);
		}
		break;

	case Crouching:
		if (!isCrouchInputReceived) {
			ApplyLocomotionState(Standing);
		}
		else if (isProneInputReceived) {
			ApplyLocomotionState(Prone);
		}
		break;

	case Prone:
		if (!isProneInputReceived) {
			if (isCrouchInputReceived) {
				ApplyLocomotionState(Crouching);
				break;
			}
			ApplyLocomotionState(Standing);
		}
		break;

	case Sprinting:
		if (!isBoosting || IsActionActive()) {
			ApplyLocomotionState(Standing);
		}
		else if (isCrouchInputReceived) {
			ApplyLocomotionState(Crouching);
		}
		else if (isProneInputReceived) {
			ApplyLocomotionState(Prone);
		}
		break;

	default:
		ApplyLocomotionState(Standing);
		break;
	}

	return CurrentLocomotionState;
}

bool ATPSCharacter::IsActionActive() const {
	return isAiming || isFiring;
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





UAbilitySystemComponent* ATPSCharacter::GetAbilitySystemComponent() const {
	return AbilitySystemComponent;
}


void ATPSCharacter::SetupInitialAbilitiesAndEffects()
{
	if (IsValid(AbilitySystemComponent) == false || IsValid(StandardAttributes) == false) {
		return;
	}

	if (IsValid(InitialAbilitySet)) {
		InitiallyGrantedAbilitySpecHandles.Append(InitialAbilitySet->GrantAbilitiesToAbilitySystem(AbilitySystemComponent));
	}

	if (IsValid(InitialGameplayEffect)) {
		AbilitySystemComponent->ApplyGameplayEffectToSelf(
			InitialGameplayEffect->GetDefaultObject<UGameplayEffect>(), 
			0, 
			AbilitySystemComponent->MakeEffectContext());
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UStandardAttributeSet::GetHealthAttribute())
		.AddUObject(this, &ThisClass::OnHealthAttributeChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UStandardAttributeSet::GetHealthMaxAttribute())
		.AddUObject(this, &ThisClass::OnHealthAttributeChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UStandardAttributeSet::GetMovementSpeedMaxAttribute())
		.AddUObject(this, &ThisClass::OnMovementAttributeChanged);
}


void ATPSCharacter::OnHealthAttributeChanged(const FOnAttributeChangeData& data) {
	UE_LOG(LogTemp, Log, TEXT("OnHealthChange"));
}

void ATPSCharacter::OnMovementAttributeChanged(const FOnAttributeChangeData& data) {
	UE_LOG(LogTemp, Log, TEXT("OnMovementChange"));
}