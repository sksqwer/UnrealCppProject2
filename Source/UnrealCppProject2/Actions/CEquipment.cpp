#include "CEquipment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CStateComponent.h"
#include "Component/CStatusComponent.h"

ACEquipment::ACEquipment()
{
	 
}

void ACEquipment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);

	Super::BeginPlay();	
}

void ACEquipment::Equip_Implementation()
{
	State->SetEquipMode();
}

void ACEquipment::Begin_Equip_Implementation()
{
}

void ACEquipment::End_Equip_Implementation()
{
}

void ACEquipment::Unequip_Implementation()
{
}
