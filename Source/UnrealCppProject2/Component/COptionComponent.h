// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COptionComponent.generated.h"


UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class UNREALCPPPROJECT2_API UCOptionComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float HorizontalLookRate = 45;

	UPROPERTY(EditAnywhere)
		float VerticalLookRate = 45;
public:
	FORCEINLINE float GetHorizontalLookRate() { return HorizontalLookRate; }
	FORCEINLINE float GetVerticalLookRate() { return VerticalLookRate; }


public:	
	UCOptionComponent();

protected:
	virtual void BeginPlay() override;

		
};
