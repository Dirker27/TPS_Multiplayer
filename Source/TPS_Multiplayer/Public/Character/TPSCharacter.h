// (C) ToasterCat Studios 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

#include "Character/TPSLocomotionState.h"
#include "Character/TPSCharacterState.h"
#include "Character/TPSCharacterBodyType.h"
#include "TPSWeaponType.h"

#include "Character/Attributes/StandardAttributeSet.h"
#include "Character/AbilitySet.h"

#include "TPSCharacter.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API ATPSCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSCharacter();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FString CharacterStateToFString(ETPSCharacterState state) {
		return FString(ETPSCharacterStateToString(state));
	};

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FString LocomotionStateToFString(ETPSLocomotionState state) {
		return FString(ETPSLocomotionStateToString(state));
	}

// UE Implementables
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

// UE Implementabes
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Overrides
	void GetActorEyesViewPoint(FVector& Location, FRotator& Rotation) const override;
	void FellOutOfWorld(const class UDamageType& dmgType) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName EyeSocketName;

	UPROPERTY(BlueprintReadOnly)
	bool IsDebugEnabled = false;

	//~ ========================================================= ~//
	//  STATE
	//~ ========================================================= ~//

	//- Identity -----------------------------------------=
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Name;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETPSCharacterBodyType> CharacterBodyType;

	//- Attributes ----------------------------------------=
	//  (sync'd from GAS attributes)
	//
	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHealth;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;
	//
	// Movement Speed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentMaxWalkSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	TEnumAsByte<ETPSCharacterState> CurrentCharacterState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETPSCharacterState> PreviousCharacterState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	TEnumAsByte<ETPSLocomotionState> CurrentLocomotionState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETPSLocomotionState> PreviousLocomotionState;

	//- Weapon State --------------------------------------=
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETPSWeaponType> EquippedWeaponType;

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

	//~ =========================================================== ~//
	//  Blueprint Logic
	//~ =========================================================== ~//

	UFUNCTION(BlueprintImplementableEvent)
	void OnFellOutOfWorld();

	UFUNCTION(BlueprintCallable)
	ETPSLocomotionState EvaluateLocomotionStateForCurrentInput();

	UFUNCTION(BlueprintCallable)
	void ApplyCharacterState(const ETPSCharacterState CharacterState);

	UFUNCTION(BlueprintCallable)
	void ApplyLocomotionState(const ETPSLocomotionState LocomotionState);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetBaseSpeedForCharacterState(const ETPSCharacterState CharacterState);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetSpeedModifierForLocomotionState(const ETPSLocomotionState LocomotionState);

	UFUNCTION(BlueprintCallable)
	float UpdateCharacterSpeedForCurrentState();

	UFUNCTION(BlueprintCallable)
	void UpdateInputContextForCurrentState();

	UFUNCTION(BlueprintCallable)
	void ApplyCharacterAttributesForCurrentState();

	UFUNCTION(BlueprintCallable)
	bool IsActionActive() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AActor* LineTrace(const UObject* WorldContextObject);



	//~ =========================================================== ~//
	//  ABILITY SYSTEM TUTORIAL
	//~ =========================================================== ~//

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override; // IAbilitySystemInterface

	void SetupInitialAbilitiesAndEffects();

	UPROPERTY(VisibleAnywhere, Category = "Abilities")
	UStandardAttributeSet* StandardAttributes{ nullptr };

protected:
	void AbilityInputBindingPressedHandler(EAbilityInput abilityInput);
	void AbilityInputBindingReleasedHandler(EAbilityInput abilityInput);

	void OnHealthAttributeChanged(const FOnAttributeChangeData&);
	void OnMovementAttributeChanged(const FOnAttributeChangeData&);

protected:
	UPROPERTY(EditAnywhere, Category="Input|Binding")
	UInputMappingContext* InputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|Binding")
	FAbilityInputBindings AbilityInputBindings;

	// <Input Actions>

	UPROPERTY(Visibleanywhere, Category="Abilities")
	UAbilitySystemComponent* AbilitySystemComponent{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	UAbilitySet* InitialAbilitySet{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TSubclassOf<UGameplayEffect> InitialGameplayEffect;

	TArray<FGameplayAbilitySpecHandle> InitiallyGrantedAbilitySpecHandles;
};
