// (C) ToasterCat Studios 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "TPSCharacterInventory.h"

#include "Ability/AbilitySet.h"
#include "Character/TPSLocomotionState.h"
#include "Character/TPSCharacterState.h"
#include "Character/TPSCharacterBodyType.h"
#include "Inventory/TPSEquipmentManager.h"
#include "Weapon/TPSWeapon.h"
#include "Weapon/TPSWeaponType.h"

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
	//- Widgets
	TObjectPtr<UWidgetComponent> UnitFrameWidget;
	TObjectPtr<UWidgetComponent> DebugFrameWidget;
	//
	//- Broadcast Delegate
	UPROPERTY(BlueprintAssignable)
	FUpdateAttributeDisplay NotifyDisplayWidgets;
private:
	bool ShouldNotify = false;

// UE Implementables
public:
	// Overrides
	void GetActorEyesViewPoint(FVector& Location, FRotator& Rotation) const override;
	void FellOutOfWorld(const class UDamageType& dmgType) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

//~ ============================================================= ~//
//  STATE
//~ ============================================================= ~//
public:

	//- Identity -----------------------------------------=
	//
	//- Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
	FString Name;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
	TEnumAsByte<ETPSCharacterBodyType> CharacterBodyType;

	//- Attributes ----------------------------------------=
	// (sync'd from GAS attributes where applicable)
	//
	//- Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State|Health", Replicated)
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State|Health")
	float MaxHealth;
	//
	//- Armor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State|Health", Replicated)
	float CurrentArmor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State|Health")
	float MaxArmor;
	//
	//- Movement Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State|Health", Replicated)
	float MovementSpeedModifier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State|Health")
	float CurrentMaxWalkSpeed;

	//- State ------------------------------------------------=
	//
	//- Character State
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State|Character", Replicated)
	TEnumAsByte<ETPSCharacterState> CurrentCharacterState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State|Character")
	TEnumAsByte<ETPSCharacterState> PreviousCharacterState;
	//
	//- Locomotion State
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State|Locomotion", Replicated)
	TEnumAsByte<ETPSLocomotionState> CurrentLocomotionState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State|Locomotion")
	TEnumAsByte<ETPSLocomotionState> PreviousLocomotionState;
	//
	// True if Character is not Incapacitated.
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsAlive() const;
	//
	// True if Crouching OR Prone.
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsCrouching() const;

	//- Weapon State --------------------------------------=
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETPSWeaponType> EquippedWeaponType;
	//
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//TPSWeapon* EquippedWeapon	{ nullptr };

	//- Controller Input ----------------------------------=
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State|Input", Replicated)
	bool IsBoosting;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State|Input", Replicated)
	bool IsCrouchInputReceived;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State|Input", Replicated)
	bool IsAiming;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State|Input", Replicated)
	bool IsFiring;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State|Input", Replicated)
	bool IsInteracting;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State|Input", Replicated)
	bool IsInMenu;

	//- Visibility ---------------------------------------=
	//
	// Shows full diagnostic data to peer client/server
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State|Render")
	bool IsDebugEnabled = false;
	//
	// Shows name/health data to peer client/server
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State|Render")
	bool ShouldRenderUnitFrame = true;

//~ ============================================================= ~//
//  Blueprint Extensions
//~ ============================================================= ~//
public:

	//- Ability Extensions ------------------------------=
	//
	//- Aim
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
	//- Fire Weapon
	UFUNCTION(BlueprintCallable)
	void StartFireWeapon();
	UFUNCTION(BlueprintImplementableEvent)
	void OnFireWeaponAbilityStart();
	//
	UFUNCTION(BlueprintCallable)
	void EndFireWeapon();
	UFUNCTION(BlueprintImplementableEvent)
	void OnFireWeaponAbilityEnd();

	//- Behavior Overrides --------------------------------=
	//
	UFUNCTION(BlueprintImplementableEvent)
	void OnFellOutOfWorld();

	//- Transforms -------------------------------------------=
	//
	//- CharacterState
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FString CharacterStateToFString(ETPSCharacterState state) {
		return FString(ETPSCharacterStateToString(state));
	};
	//
	//- LocomotionState
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FString LocomotionStateToFString(ETPSLocomotionState state) {
		return FString(ETPSLocomotionStateToString(state));
	}

//~ ================================================================ ~//
//  Character Logic
//~ ================================================================ ~//

private:
	// Called every frame.
	//  Set state-driven values in subcomponents.
	void SyncComponentsFromState();

public:
	// Call after every action that modifies state.
	UFUNCTION(BlueprintCallable)
	void EvaluateStateAndApplyUpdates();

	//- Modify Behavioral States --------------------------=
	//
	//- CharacterState
	UFUNCTION(BlueprintCallable)
	void ApplyCharacterState(const ETPSCharacterState CharacterState);
	UFUNCTION(BlueprintCallable)
	void RevertCharacterState();
	//
	//- LocomotionState
	UFUNCTION(BlueprintCallable)
	void ApplyLocomotionState(const ETPSLocomotionState LocomotionState);
	UFUNCTION(BlueprintCallable)
	void RevertLocomotionState();

protected:
	//- Logic ---------------------------------------------=
	// 
	//- Determine what state we should be in.
	UFUNCTION(BlueprintCallable)
	ETPSLocomotionState EvaluateLocomotionStateForCurrentInput();
	//
	//- Calculate Speed
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetBaseSpeedForCharacterState(const ETPSCharacterState CharacterState);
	//
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetSpeedModifierForLocomotionState(const ETPSLocomotionState LocomotionState);
	//
	//- Apply calculated MovementSpeed
	UFUNCTION(BlueprintCallable)
	float UpdateCharacterSpeedForCurrentState();
	//
	//- Swap out available Input Actions
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
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	UAbilitySet* InitialAbilitySet{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
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
	UPROPERTY(EditAnywhere, Category="Inventory")
	TObjectPtr<UTPSEquipmentManager> EquipmentManager;
	UPROPERTY(EditAnywhere, Category="Inventory")
	TObjectPtr<UTPSCharacterInventory> Inventory;

//~ ============================================================= ~//
//  CONFIGURATION
//~ ============================================================= ~//
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	FName EyeSocketName;
};