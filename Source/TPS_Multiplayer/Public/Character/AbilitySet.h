#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpecHandle.h"

#include "AbilitySet.generated.h"


UENUM(BlueprintType)
enum class EAbilityInput : uint8
{
	None = 0,
	Interact = 1,

	// Locomotion
	Mantle = 2,
	Crouch = 3,
	Boost = 4,
	UnBoost = 5,

	// Primary Actions
	PrimaryAttack = 6,
	SecondaryAttack = 7,
	Aim = 8,

	// Inventory
	Equip = 9,
	UnEquip = 10,

	// Weapon Handling
	Reload = 11
};


USTRUCT()
struct FAbilityInputToInputActionBinding
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction;

	UPROPERTY(EditDefaultsOnly)
	EAbilityInput AbilityInput;
};


USTRUCT()
struct FAbilityInputBindings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TArray<FAbilityInputToInputActionBinding> Bindings;
};

USTRUCT()
struct FAbilitySystem
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Ability")
	TSubclassOf<UGameplayAbility> GameplayAbility;

	UPROPERTY(EditDefaultsOnly, Category="Ability")
	EAbilityInput InputKey;
};


UCLASS()
class TPS_MULTIPLAYER_API UAbilitySet : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Ability")
	TArray<FAbilitySystem> AbilitySetItems;

	TArray<FGameplayAbilitySpecHandle> GrantAbilitiesToAbilitySystem(UAbilitySystemComponent* AbilitySystemComponent) const;
};
