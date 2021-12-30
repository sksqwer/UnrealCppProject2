#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICharacter.generated.h"

UINTERFACE(MinimalAPI)
class UICharacter : public UInterface
{
	GENERATED_BODY()
};

class UNREALCPPPROJECT2_API IICharacter
{
	GENERATED_BODY()
		
public:
	virtual void ChangeColor(FLinearColor InColor) = 0;
	virtual void Begin_Dead() {}
	virtual void End_Dead() {}
};
