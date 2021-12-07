#include "CActionComponent.h"
#include "Global.h"

UCActionComponent::UCActionComponent()
{
}


// Called when the game starts
void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void UCActionComponent::ChangeType(EActionType InNewType)
{
	EActionType prevType = Type;
	Type = InNewType;

	if(OnActionTypeChanged.IsBound())
	{
		OnActionTypeChanged.Broadcast(prevType, InNewType);
	}
}

void UCActionComponent::SetMode(EActionType InType)
{
	if(Type == InType)
	{
		SetUnarmedMode();
		return;
	}
	else if(IsUnarmedMode() == false)
	{
		// : Unequip weapon
	}

	// : equip weapon

	ChangeType(InType);



}

void UCActionComponent::SetUnarmedMode()
{
	SetMode(EActionType::Unarmed);
}

void UCActionComponent::SetOneHandMode()
{
	SetMode(EActionType::OneHand);
}

void UCActionComponent::SetTwoHandMode()
{
	SetMode(EActionType::TwoHand);
}
