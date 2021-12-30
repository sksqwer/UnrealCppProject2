#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Warp.generated.h"

UCLASS()
class UNREALCPPPROJECT2_API ACDoAction_Warp : public ACDoAction
{
	GENERATED_BODY()
		
private:
	virtual void BeginPlay() override;

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;
	virtual void Tick(float DeltaTime) override;

private:
	class UDecalComponent* Decal;
	FVector Location;
		
private:
	bool GetCursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotation);
};
