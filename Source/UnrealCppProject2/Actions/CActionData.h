#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData.generated.h"

USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;
	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;
	UPROPERTY(EditAnywhere)
		FName StartSection;
	UPROPERTY(EditAnywhere)
		bool bCanMove = true;
};

UCLASS()
class UNREALCPPPROJECT2_API UCActionData : public UDataAsset
{
	GENERATED_BODY()

private:
	class ACEquipment* Equipment;

	void BeginPlay(class ACharacter* InOwnerCharacter);

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACEquipment> EquipmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FEquipmentData EquipmentData;
	
};
