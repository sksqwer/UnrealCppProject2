#include "CDoAction_Throw.h"

#include "Constraint.h"
#include "Global.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Character.h"
#include "Actions/CAim.h"
#include "Component/CStateComponent.h"
#include "Component/CStatusComponent.h"

void ACDoAction_Throw::BeginPlay()
{
	Super::BeginPlay();

	Aim = NewObject<UCAim>();
	Aim->BeginPlay(OwnerCharacter);
}

void ACDoAction_Throw::DoAction()
{
	Super::DoAction();

	Super::DoAction();
	CheckFalse(State->IsIdleMode());
	State->SetActionMode();
	
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage,
		Datas[0].PlayRatio,
		Datas[0].StartSection);

	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Throw::Begin_DoAction()
{
	Super::Begin_DoAction();
}

void ACDoAction_Throw::End_DoAction()
{
	Super::End_DoAction();

	State->SetIdleMode();
	Status->SetMove();
}

void ACDoAction_Throw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Aim->Tick(DeltaTime);
}

void ACDoAction_Throw::OnAim()
{
	Super::OnAim();

	Aim->OnAim();
}

void ACDoAction_Throw::OffAim()
{
	Super::OffAim();

	Aim->OffAim();
}
