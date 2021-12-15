#include "CAnimNotifyState_EnableCombo.h"
#include "Global.h"
#include "Actions/CEquipment.h"
#include "Actions/CDoAction_Melee.h"
#include "Component/CActionComponent.h"


FString UCAnimNotifyState_EnableCombo::GetNotifyName_Implementation() const
{
	return "EnableCombo";
}

void UCAnimNotifyState_EnableCombo::NotifyBegin(
	USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(action);
	
	// enable combo
	ACDoAction_Melee* melee = Cast<ACDoAction_Melee>(action->GetCurrent()->GetDoAction());
	CheckNull(melee);

	melee->EnableCombo();
}

void UCAnimNotifyState_EnableCombo::NotifyEnd(
	USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action =
		CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(action);
	
	// disable combo
	ACDoAction_Melee* melee = Cast<ACDoAction_Melee>(action->GetCurrent()->GetDoAction());
	CheckNull(melee);

	melee->DisableCombo();
}

