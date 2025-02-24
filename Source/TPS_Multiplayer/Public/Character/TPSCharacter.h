// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "TPSCharacterConfiguration.h"
#include "TPSCharacterInventory.h"

#include "GAS/GASAbilitySet.h"
#include "Character/TPSLocomotionState.h"
#include "Character/TPSCharacterState.h"
#include "Character/TPSCharacterBodyType.h"
#include "Inventory/TPSEquipmentManager.h"
#include "Weapon/TPSWeapon.h"

#include "TPSCharacter.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateAttributeDisplay);

UCLASS()
class TPS_MULTIPLAYER_API ATPSCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSCharacter();

// UE Implementables
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

//~ ============================================================= ~//
//  COMPONENTS
//~ ============================================================= ~//
public:
	//- Display Widgets --------------------------------------=
	//
	//- Broadcast Delegate
	UPROPERTY(BlueprintAssignable)
	FUpdateAttributeDisplay NotifyDisplayWidgets;
private:
	bool ShouldNotify = false;

// UE Implementables
public:
	// Overrides
	void FellOutOfWorld(const class UDamageType& dmgType) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

//~ ============================================================= ~//
//  STATE
//~ ============================================================= ~//
public:

	//////////////////////////////////////////////////////
	// Identity
	
	// Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|Identity")
	FString Name;

	//////////////////////////////////////////////////////
	// Configuration

	// Character Configuration
	//   Will be overridden by PlayerState on Possession.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|Configuration")
	TObjectPtr<UTPSCharacterConfiguration> Configuration;

	//////////////////////////////////////////////////////
	// Attributes
	//   (sync'd from GAS attributes where applicable)
	
	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Health", Replicated)
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Health")
	float MaxHealth;

	// Armor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Health", Replicated)
	float CurrentArmor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Health")
	float MaxArmor;

	// Movement Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Health", Replicated)
	float MovementSpeedModifier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Health")
	float CurrentMaxWalkSpeed;

	//////////////////////////////////////////////////////
	// State

	// Character State
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Character", Replicated)
	TEnumAsByte<ETPSCharacterState> CurrentCharacterState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Character")
	TEnumAsByte<ETPSCharacterState> PreviousCharacterState;
	//
	// Locomotion State
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Locomotion", Replicated)
	TEnumAsByte<ETPSLocomotionState> CurrentLocomotionState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Locomotion")
	TEnumAsByte<ETPSLocomotionState> PreviousLocomotionState;
	//
	// IsAlive (Synthetic)
	//   True if Character is not Incapacitated.
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsAlive() const;
	//
	// IsCrouching (Synthetic)
	//   True if Crouching OR Prone.
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsCrouching() const;
	//
	// IsIdle (Synthetic)
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsIdle() const;
	//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float IdleSeconds;
	//
	// Current Accuracy Tolerance
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FVector2D GetCurrentAccuracyTolerance() const;

	////////////////////////////////////////////////////////
	// Equipment State

	// Current Equipped Weapon (Synthetic)
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ATPSWeapon* GetEquippedWeapon() const;

	////////////////////////////////////////////////////////
	// Controller Input

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Input", Replicated)
	FRotator TargetLookRotation;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Input", Replicated)
	bool IsBoosting;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Input", Replicated)
	bool IsCrouchInputReceived;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Input", Replicated)
	bool IsAiming;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Input", Replicated)
	bool IsFiring;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Input", Replicated)
	bool IsEquipping;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Input", Replicated)
	bool IsReloading;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Input", Replicated)
	bool IsInteracting;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Input", Replicated)
	bool IsInMenu;

	//////////////////////////////////////////////////////
	// UI Visibility

	// Shows full diagnostic data to peer client/server
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Render")
	bool IsDebugEnabled = false;
	//
	// Shows name/health data to peer client/server
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Render")
	bool ShouldRenderUnitFrame = true;
	//
	// Shows simple debug data to peer client
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|State|Render")
	bool ShouldRenderDebugFrame = true;

//~ ============================================================= ~//
//  Blueprint Extensions
//~ ============================================================= ~//
public:

	////////////////////////////////////////////////////////
	// Ability Extensions
	
	// Boost
	UFUNCTION(BlueprintCallable)
	void StartBoost();
	UFUNCTION(BlueprintImplementableEvent)
	void OnBoostAbilityStart();
	//
	UFUNCTION(BlueprintCallable)
	void EndBoost();
	UFUNCTION(BlueprintImplementableEvent)
	void OnBoostAbilityEnd();
	//
	// Aim
	UFUNCTION(BlueprintCallable)
	void StartAim();
	UFUNCTION(BlueprintImplementableEvent)
	void OnAimAbilityStart();
	//
	UFUNCTION(BlueprintCallable)
	void EndAim();
	UFUNCTION(BlueprintImplementableEvent)
	void OnAimAbilityEnd();
	//
	// Fire Weapon
	UFUNCTION(BlueprintCallable)
	void StartFireWeapon();
	UFUNCTION(BlueprintImplementableEvent)
	void OnFireWeaponAbilityStart();
	// Called when fire is actually performed to trigger animations
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnFirePerformed();
	//
	UFUNCTION(BlueprintCallable)
	void EndFireWeapon();
	UFUNCTION(BlueprintImplementableEvent)
	void OnFireWeaponAbilityEnd();
	//
	// EquipWeapon ("Ready")
	UFUNCTION(BlueprintCallable)
	void StartEquipWeapon();
	UFUNCTION(BlueprintImplementableEvent)
	void OnEquipWeaponAbilityStart();
	//
	UFUNCTION(BlueprintCallable)
	void EndEquipWeapon();
	UFUNCTION(BlueprintImplementableEvent)
	void OnEquipWeaponAbilityEnd();
	//
	// UnEquipWeapon ("UnReady")
	UFUNCTION(BlueprintCallable)
	void StartUnEquipWeapon();
	UFUNCTION(BlueprintImplementableEvent)
	void OnUnEquipWeaponAbilityStart();
	//
	UFUNCTION(BlueprintCallable)
	void EndUnEquipWeapon();
	UFUNCTION(BlueprintImplementableEvent)
	void OnUnEquipWeaponAbilityEnd();
	//
	// Reload Weapon
	UFUNCTION(BlueprintCallable)
	void StartReloadWeapon();
	UFUNCTION(BlueprintImplementableEvent)
	void OnReloadWeaponAbilityStart();
	//
	UFUNCTION(BlueprintCallable)
	void EndReloadWeapon();
	UFUNCTION(BlueprintImplementableEvent)
	void OnReloadWeaponAbilityEnd();
	//
	// Interact
	UFUNCTION(BlueprintCallable)
	void StartInteract();
	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractAbilityStart();
	//
	UFUNCTION(BlueprintCallable)
	void EndInteract();
	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractAbilityEnd();


	////////////////////////////////////////////////////////
	// Behavior Overrides

	UFUNCTION(BlueprintImplementableEvent)
	void OnFellOutOfWorld();


	////////////////////////////////////////////////////////
	// Type Transforms

	// CharacterState
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FString CharacterStateToFString(ETPSCharacterState state) {
		return FString(ETPSCharacterStateToString(state));
	};
	//
	// LocomotionState
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FString LocomotionStateToFString(ETPSLocomotionState state) {
		return FString(ETPSLocomotionStateToString(state));
	}

//~ ================================================================ ~//
//  Character Business Logic
//~ ================================================================ ~//

private:
	// Called every frame.
	//  Set state-driven values in subcomponents.
	void SyncComponentsFromState();

public:

	////////////////////////////////////////////////////////
	// State Modifiers

	// CharacterState
	UFUNCTION(BlueprintCallable)
	void ApplyCharacterState(const ETPSCharacterState CharacterState);
	UFUNCTION(BlueprintCallable)
	void RevertCharacterState();
	//
	// LocomotionState
	UFUNCTION(BlueprintCallable)
	void ApplyLocomotionState(const ETPSLocomotionState LocomotionState);
	UFUNCTION(BlueprintCallable)
	void RevertLocomotionState();


	////////////////////////////////////////////////////////
	// Business Logic

	// Determine what state we should be in.
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ETPSLocomotionState EvaluateLocomotionStateForCurrentInput();
	//
	// Calculate Speed
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetBaseSpeedForCharacterState(const ETPSCharacterState CharacterState);
	//
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetSpeedModifierForLocomotionState(const ETPSLocomotionState LocomotionState);
	//
	// Apply calculated MovementSpeed
	UFUNCTION(BlueprintCallable)
	float UpdateCharacterSpeedForCurrentState();
	//
	// Swap out available Input Actions
	UFUNCTION(BlueprintCallable)
	void UpdateInputContextForCurrentState();

	UFUNCTION(BlueprintCallable)
	bool IsActionActive() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AActor* LineTrace(const UObject* WorldContextObject);

//~ ============================================================= ~//
//  ABILITY SYSTEM WIRING
//~ ============================================================= ~//
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override; // IAbilitySystemInterface

	UFUNCTION(BlueprintCallable)
	void SyncAttributesFromGAS();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "TPSCharacter|Abilities")
	UAbilitySet* InitialAbilitySet{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "TPSCharacter|Abilities")
	TSubclassOf<UGameplayEffect> InitialGameplayEffect;

	TArray<FGameplayAbilitySpecHandle> InitiallyGrantedAbilitySpecHandles;

protected:
	void SetupInitialAbilitiesAndEffects();
	void OnArmorAttributeChanged(const FOnAttributeChangeData&);
	void OnHealthAttributeChanged(const FOnAttributeChangeData&);
	void OnMovementAttributeChanged(const FOnAttributeChangeData&);

//~ ============================================================= ~//
//  INVENTORY SYSTEM
//~ ============================================================= ~//
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TPSCharacter|Inventory")
	TObjectPtr<UTPSEquipmentManager> EquipmentManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TPSCharacter|Inventory")
	TObjectPtr<UTPSCharacterInventory> Inventory;


//~ ============================================================= ~//
//  EVENT OVERRIDES
//~ ============================================================= ~//

public:

	// Use Actor's Eyes at Mesh Location for detection and docking sweeps
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPSCharacter|Configuration")
	FName EyeSocketName;
	virtual void GetActorEyesViewPoint(FVector& Location, FRotator& Rotation) const override;

	// Apply damage via Ability System (if present)
	//virtual float TakeDamage(float damage, struct FDamageEvent const& event, AController* instigator, AActor* causer) override;
};