#include "CActionComponent.h"
#include "Global.h"
#include "Actions/CActionData.h"
#include "Actions/CAttachment.h"
#include "Actions/CDoAction.h"
#include "GameFramework/Character.h"
#include "Actions/CEquipment.h"

UCActionComponent::UCActionComponent()
{
}


// Called when the game starts
void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* character = Cast<ACharacter>(GetOwner());
	for(int32 i = 0; i < (int32)EActionType::Max; i++)
	{
		if (!!Datas[i])
			Datas[i]->BeginPlay(character);
		else
		{
			CLog::Log(character->GetName());
			CLog::Log(i);
		}
	}
	
	
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
	if (Type == InType)
	{
		SetUnarmedMode();
		return;
	}
	else if (IsUnarmedMode() == false)
	{
		// ���� ����
		ACEquipment* equipment = Datas[(int32)Type]->GetEquipment();
		CheckNull(equipment);
		equipment->Unequip();
	}

	// ���� ����
	if (!!Datas[(int32)InType])
	{
		ACEquipment* equipment = Datas[(int32)InType]->GetEquipment();
		CheckNull(equipment);
		equipment->Equip();
	}

	ChangeType(InType);

}

void UCActionComponent::SetUnarmedMode()
{
	if(!!Datas[(int32)Type])
	{
		ACEquipment* equipment = Datas[(int32)Type]->GetEquipment();
		CheckNull(equipment);

		equipment->Unequip();
	}

	// >> :
	//if (!!Datas[(int32)EActionType::Unarmed])
	//{
	//	ACEquipment* equipment = Datas[(int32)EActionType::Unarmed]->GetEquipment();
	//	CheckNull(equipment);
	//	equipment->Equip();
	//}
	// << :

	ChangeType(EActionType::Unarmed);
}

void UCActionComponent::SetFistMode()
{
	CLog::Log("Fist_Mode");
	SetMode(EActionType::Fist);
}

void UCActionComponent::SetOneHandMode()
{
	SetMode(EActionType::OneHand);
}

void UCActionComponent::SetTwoHandMode()
{
	SetMode(EActionType::TwoHand);
}

void UCActionComponent::SetWarpMode()
{
	SetMode(EActionType::Warp);
}

void UCActionComponent::SetFireStromMode()
{
	SetMode(EActionType::FireStrom);
}

void UCActionComponent::SetIceBallMode()
{
	SetMode(EActionType::IceBall);
}

void UCActionComponent::DoAction()
{
	CheckTrue(IsUnarmedMode());
	
	if(!!Datas[(int32)Type])
	{
		ACDoAction* action = Datas[(int32)Type]->GetDoAction();

		if(!!action)
		{
			action->DoAction();
		}
	}
}

void UCActionComponent::OffAllCollision()
{
	for (UCActionData* data : Datas)
	{
		if (!!data == false)
			continue;

		if (!!data->GetAttachment() == false)
			continue;

		data->GetAttachment()->OffCollision();
	}
}

void UCActionComponent::DoAim(bool InAim)
{
	CheckTrue(IsUnarmedMode());

	if(!!Datas[(int32)Type])
	{
		ACDoAction* action = Datas[(int32)Type]->GetDoAction();
		if (!!action)
			InAim ? action->OnAim() : action->OffAim();

	}
}
