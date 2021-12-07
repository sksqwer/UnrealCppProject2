#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Unarmed,
	OneHand,
	TwoHand,
	Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionTypeChanged, EActionType, InPrevType, EActionType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCPPPROJECT2_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCActionComponent();

protected:
	virtual void BeginPlay() override;

private:
	EActionType Type;

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmedMode() { if (Type == EActionType::Unarmed) return true; else return false; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsOneHandMode() { if (Type == EActionType::OneHand) return true; else return false; }

	UFUNCTION(BlueprintPure)	
		FORCEINLINE bool IsTwosHandMode() { if (Type == EActionType::OneHand) return true; else return false; }

public:
	UPROPERTY(BlueprintAssignable)
		FActionTypeChanged OnActionTypeChanged;

private:
	void ChangeType(EActionType InNewType);
	void SetMode(EActionType InType);

public:
	void SetUnarmedMode();
	void SetOneHandMode();
	void SetTwoHandMode();
};
