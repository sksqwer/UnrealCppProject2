// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSceonds)
{
	Super::NativeUpdateAnimation(DeltaSceonds);

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character);

	Speed = character->GetVelocity().Size2D();
	Direction = CalculateDirection(character->GetVelocity(), character->GetControlRotation());
}
