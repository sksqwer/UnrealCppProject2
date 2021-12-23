#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "Utilities/CLog.h"
#include "CDoAction_Melee.generated.h"

UCLASS()
class UNREALCPPPROJECT2_API ACDoAction_Melee : public ACDoAction
{
	GENERATED_BODY()

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

private:
	bool bExist;
	bool bEnable;
	bool bLast;
	int32 Index;

public:
	FORCEINLINE void EnableCombo() { CLog::Log("Combo!"); bEnable = true; }
	FORCEINLINE void DisableCombo() { CLog::Log("ComboX"); bEnable = false; }

	virtual void OnAttachmentBeginOverlap(
		class ACharacter* InAttacker,
		class AActor* InAttackCauser,
		class ACharacter* InOtherCharacter) override;

	virtual void OnAttachmentEndOverlap(
		class ACharacter* InAttacker,
		class AActor* InAttackCauser,
		class ACharacter* InOtherCharacter) override;

};
