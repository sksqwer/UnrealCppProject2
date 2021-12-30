#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actions/CActionData.h"
#include "CDoAction.generated.h"

UCLASS()
class UNREALCPPPROJECT2_API ACDoAction : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDoAction();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;

public:
	virtual void DoAction() {}
	virtual void Begin_DoAction() {}
	virtual void End_DoAction() {}

	virtual void OnAim() {}
	virtual void OffAim() {}

protected:
	TArray<FDoActionData> Datas;

public:
	FORCEINLINE void SetDatas(TArray<FDoActionData> InDatas) { Datas = InDatas; }

public:
	UFUNCTION()
		virtual void OnAttachmentBeginOverlap(
			class ACharacter* InAttacker,
			class AActor* InAttackCauser,
			class ACharacter* InOtherCharacter)
	{}


	UFUNCTION()
		virtual void OnAttachmentEndOverlap(
			class ACharacter* InAttacker,
			class AActor* InAttackCauser,
			class ACharacter* InOtherCharacter)
	{}


	UFUNCTION()
		virtual void OnAttachmentCollision()
	{}
	
	UFUNCTION()
		virtual void OffAttachmentCollision()
	{}

protected:
	const bool* bEquipped;

public:
	FORCEINLINE void SetEquipped(const bool* InEquipped) { bEquipped = InEquipped; }
};
