#include "CAnimNotify_BeginAction.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Actions/CActionData.h"
#include "Actions/CDoAction.h"
#include "Component/CActionComponent.h"


FString UCAnimNotify_BeginAction::GetNotifyName_Implementation() const
{
	return "BeginAction";
}

void UCAnimNotify_BeginAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());

	CheckNull(action);
	CheckNull(action->GetCurrent());
	CheckNull(action->GetCurrent()->GetDoAction());

	action->GetCurrent()->GetDoAction()->Begin_DoAction();

}
