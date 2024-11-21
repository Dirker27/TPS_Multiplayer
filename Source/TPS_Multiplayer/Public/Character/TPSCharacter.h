// (C) ToasterCat Studios 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

#include "Ability/AbilitySet.h"
#include "Character/TPSLocomotionState.h"
#include "Character/TPSCharacterState.h"
#include "Character/TPSCharacterBodyType.h"
#include "Weapon/TPSWeapon.h"
#include "Weapon/TPSWeaponType.h"

#include "TPSCharacter.generated.h"

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

public:
//~ ============================================================= ~//
//  COMPONENTS
//~ ============================================================= ~//
	//TObjectPtr<UWidget> UnitFrameWidget;
	//TObjectPtr<UWidget> DebugFrameWidget;

	UDELEGATE(BlueprintAuthorityOnly)
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateAttributeDisplay);
	UPROPERTY(BlueprintAssignable)
	FUpdateAttributeDisplay updateDelegate;
	//updateDelegate.BindSP()
 

// UE Implementables
public:
	// Overrides
	void GetActorEyesViewPoint(FVector& Location, FRotator& Rotation) const override;
	void FellOutOfWorld(const class UDamageType& dmgType) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName EyeSocketName;

//~ ============================================================= ~//
//  STATE
//~ ============================================================= ~//
public:
	UPROPERTY(BlueprintReadOnly)
	bool IsDebugEnabled = false;
	
	//- Identity -----------------------------------------=
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETPSCharacterBodyType> CharacterBodyType;

	//- Attributes ----------------------------------------=
	//  (sync'd from GAS attributes)
	//
	//- Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;
	//
	//- Armor
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentArmor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxArmor;
	//
	//- Movement Speed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MovementSpeedModifier;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentMaxWalkSpeed;

	//- State ------------------------------------------------=
	//
	//- Character State
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated)
	TEnumAsByte<ETPSCharacterState> CurrentCharacterState;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<ETPSCharacterState> PreviousCharacterState;
	//
	//- Locomotion State
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated)
	TEnumAsByte<ETPSLocomotionState> CurrentLocomotionState;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<ETPSLocomotionState> PreviousLocomotionState;

	//- Weapon State --------------------------------------=
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETPSWeaponType> EquippedWeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ATPSWeapon* EquippedWeapon	{ nullptr };

	// True if Crouching OR Prone.
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsCrouching() const;

	//- Controller Input ----------------------------------=
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	bool IsBoosting;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsCrouchInputReceived;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	bool IsAiming;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	bool IsFiring;

//~ ============================================================= ~//
//  Blueprint Extensions
//~ ============================================================= ~//
public:
	// From UE Demo
	UFUNCTION(BlueprintImplementableEvent)
	void OnFellOutOfWorld();

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

public:
	UFUNCTION(BlueprintCallable)
	void ApplyCharacterState(const ETPSCharacterState CharacterState);

	UFUNCTION(BlueprintCallable)
	void RevertCharacterState();

	UFUNCTION(BlueprintCallable)
	void ApplyLocomotionState(const ETPSLocomotionState LocomotionState);

	UFUNCTION(BlueprintCallable)
	void RevertLocomotionState();



	UFUNCTION(BlueprintCallable)
	void EvaluateStateAndApplyUpdates();



	UFUNCTION(BlueprintCallable)
	ETPSLocomotionState EvaluateLocomotionStateForCurrentInput();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetBaseSpeedForCharacterState(const ETPSCharacterState CharacterState);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetSpeedModifierForLocomotionState(const ETPSLocomotionState LocomotionState);

	UFUNCTION(BlueprintCallable)
	float UpdateCharacterSpeedForCurrentState();

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

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	UAbilitySet* InitialAbilitySet{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UGameplayEffect> InitialGameplayEffect;

	TArray<FGameplayAbilitySpecHandle> InitiallyGrantedAbilitySpecHandles;

private:
	void SetupInitialAbilitiesAndEffects();
	void OnArmorAttributeChanged(const FOnAttributeChangeData&);
	void OnHealthAttributeChanged(const FOnAttributeChangeData&);
	void OnMovementAttributeChanged(const FOnAttributeChangeData&);
};
