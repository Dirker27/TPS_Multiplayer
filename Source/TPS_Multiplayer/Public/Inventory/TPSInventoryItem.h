#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Rendering/SkeletalMeshModel.h"

#include "TPSInventoryItem.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API UTPSInventoryItem : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Identity")
	FName Name;

	//UPROPERTY(EditAnywhere, Category = "Identity")
	//TObjectPtr<FSkeletalMeshModel> Avatar;

	UPROPERTY(EditAnywhere)
	bool IsStackable;

	UPROPERTY(EditAnywhere)
	int Quantity;
};