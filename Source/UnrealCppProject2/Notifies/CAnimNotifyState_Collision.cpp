#include "CAnimNotifyState_Collision.h"
#include "Global.h"
#include "Actions/CActionData.h"
#include "Actions/CAttachment.h"
#include "Component/CActionComponent.h"

FString UCAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action =
		CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());

	CheckNull(action);

	ACAttachment* attachment = action->GetCurrent()->GetAttachment();
	CheckNull(attachment);

	attachment->OnCollision();
}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action =
		CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());

	CheckNull(action);

	ACAttachment* attachment = action->GetCurrent()->GetAttachment();
	CheckNull(attachment);

	attachment->OffCollision();
}
