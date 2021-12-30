#include "CDoAction_FireStorm.h"
#include "Global.h"
#include "CAttachment.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Character.h"
#include "Component/CStateComponent.h"
#include "Component/CStatusComponent.h"

void ACDoAction_FireStorm::BeginPlay()
{
	Super::BeginPlay();

	for(AActor* actor : OwnerCharacter->Children)
	{
		if(actor->IsA<ACAttachment>() && actor->GetActorLabel().Contains("FireStorm"))
		{
			Box = CHelpers::GetComponent<UBoxComponent>(actor);
		}
	}

}

void ACDoAction_FireStorm::DoAction()
{
	Super::DoAction();
	CheckFalse(State->IsIdleMode());
	State->SetActionMode();

	Angle = UKismetMathLibrary::RandomFloatInRange(0, 360);
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage,
		Datas[0].PlayRatio,
		Datas[0].StartSection);

	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();

}

void ACDoAction_FireStorm::Begin_DoAction()
{
	Super::Begin_DoAction();
	Attached = UGameplayStatics::SpawnEmitterAttached(Datas[0].Effect, Box, "");
	Attached->SetRelativeLocation(Datas[0].EffectTransform.GetLocation());
	Attached->SetRelativeScale3D(Datas[0].EffectTransform.GetScale3D());

	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner());
	attachment->OnCollision();

	UKismetSystemLibrary::K2_SetTimer(this, "Hitted", HittedTime, true);
}

void ACDoAction_FireStorm::End_DoAction()
{
	Super::End_DoAction();

	Status->SetMove();
	
	FTimerDynamicDelegate timerDelegate;

	timerDelegate.BindUFunction(this, "Finish");

	UKismetSystemLibrary::K2_SetTimerDelegate(timerDelegate, Time, false);



}

void ACDoAction_FireStorm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(*bEquipped);
	CheckFalse(State->IsActionMode());

	FVector location = OwnerCharacter->GetActorLocation();

	Angle += Speed * DeltaTime;
	if (FMath::IsNearlyEqual(Angle, 360))
		Angle = 0.0f;

	FVector axis = FVector(Distance, 0, 0);
	FVector value = axis.RotateAngleAxis(Angle, FVector(0, 0, 1));

	location += value;
	Box->SetWorldLocation(location);

}

void ACDoAction_FireStorm::Finish()
{
	State->SetIdleMode();
	Attached->DestroyComponent();
	UKismetSystemLibrary::K2_ClearTimer(this, "Hitted");
}

void ACDoAction_FireStorm::Hitted()
{
	FDamageEvent e;
	for(ACharacter* character : HittedCharacter)
	{
		character->TakeDamage(Datas[0].Power, e, OwnerCharacter->GetController(), this);
	}
}

void ACDoAction_FireStorm::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCauser,
                                                    ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCauser, InOtherCharacter);

	HittedCharacter.AddUnique(InOtherCharacter);

}

void ACDoAction_FireStorm::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InAttackCauser,
	ACharacter* InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InAttacker, InAttackCauser, InOtherCharacter);

	HittedCharacter.Remove(InOtherCharacter);
}
