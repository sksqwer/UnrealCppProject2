#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Unarmed,
	Fist,
	OneHand,
	TwoHand,
	Warp,
	FireStrom,
	IceBall,
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
		FORCEINLINE bool IsFistMode() { if (Type == EActionType::Fist) return true; else return false; }

	UFUNCTION(BlueprintPure)	
		FORCEINLINE bool IsTwosHandMode() { if (Type == EActionType::OneHand) return true; else return false; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsWarpMode() { if (Type == EActionType::Warp) return true; else return false; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsFireStromMode() { if (Type == EActionType::FireStrom) return true; else return false; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsIceBallMode() { if (Type == EActionType::IceBall) return true; else return false; }

public:
	UPROPERTY(BlueprintAssignable)
		FActionTypeChanged OnActionTypeChanged;

private:
	void ChangeType(EActionType InNewType);
	void SetMode(EActionType InType);

public:
	void SetUnarmedMode();
	void SetFistMode();
	void SetOneHandMode();
	void SetTwoHandMode();
	void SetWarpMode();
	void SetFireStromMode();
	void SetIceBallMode();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
		class UCActionData* Datas[(int32)EActionType::Max];

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCActionData* GetCurrent() { return Datas[(int32)Type]; }

public:
	void DoAction();
	void OffAllCollision();
	void DoAim(bool InAim);

};
