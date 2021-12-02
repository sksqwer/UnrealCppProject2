#include "CStateComponent.h"
#include "Global.h"

UCStateComponent::UCStateComponent()
{
	
}


void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void UCStateComponent::ChangeType(EStateType InType)
{
	EStateType type = Type;
	Type = InType;

	if(OnStateTypeChanged.IsBound())
	{
		OnStateTypeChanged.Broadcast(type, InType);
	}

}

void UCStateComponent::SetIdleMode()
{
	ChangeType(EStateType::Idle);
}

void UCStateComponent::SetRollMode()
{
	ChangeType(EStateType::Roll);
}

void UCStateComponent::SetBackStepMode()
{
	ChangeType(EStateType::Backstep);
}
