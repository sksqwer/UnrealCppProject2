#include "CDoAction_Warp.h"
#include "Global.h"
#include "CAttachment.h"
#include "GameFramework/Character.h"
#include "Components/DecalComponent.h"
#include "Component/CStateComponent.h"
#include "Component/CStatusComponent.h"


void ACDoAction_Warp::BeginPlay()
{
	Super::BeginPlay();
	
	for (AActor* actor : OwnerCharacter->Children)
	{
		if (actor->IsA<ACAttachment>() && actor->GetActorLabel().Contains("Warp"))
		{
			Decal = CHelpers::GetComponent<UDecalComponent>(actor);
			break;
		}
	}
}

void ACDoAction_Warp::DoAction()
{
	//Super::DoAction();

	CheckFalse(*bEquipped);

	FRotator rotator;
	CheckFalse(GetCursorLocationAndRotation(Location, rotator));

	CheckFalse(State->IsIdleMode());
	State->SetActionMode();

	Decal->SetWorldLocation(Location);
	Decal->SetWorldRotation(rotator);

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage,
		Datas[0].PlayRatio,
		Datas[0].StartSection);

	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Warp::Begin_DoAction()
{
	//Super::Begin_DoAction();

	FTransform transform = Datas[0].EffectTransform;
	//transform.AddToTranslation(OwnerCharacter->GetActorLocation());
	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Datas[0].Effect, transform);

	UGameplayStatics::SpawnEmitterAttached(Datas[0].Effect, OwnerCharacter->GetMesh(),
		"", transform.GetLocation(), FRotator(transform.GetRotation()),
		transform.GetScale3D());
}

void ACDoAction_Warp::End_DoAction()
{
	//Super::End_DoAction();
	OwnerCharacter->SetActorLocation(Location);
	Location = FVector::ZeroVector;
	//Decal->

	State->SetIdleMode();
	Status->SetMove();
}
void ACDoAction_Warp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(*bEquipped);

	FVector location;
	FRotator rotator;
	if(!!Decal)
	{
		if (GetCursorLocationAndRotation(location, rotator))
		{
			Decal->SetVisibility(true);
			Decal->SetWorldLocation(location);
			Decal->SetWorldRotation(rotator);
			return;
		}

		Decal->SetVisibility(false);		
	}
	
}

bool ACDoAction_Warp::GetCursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotation)
{
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	TArray<TEnumAsByte<EObjectTypeQuery>> objects;

	objects.Add(EObjectTypeQuery::ObjectTypeQuery1);

	FHitResult hitResult;
	if(controller->GetHitResultUnderCursorForObjects(objects, false, hitResult))
	{
		OutLocation = hitResult.Location;
		OutRotation = hitResult.ImpactNormal.Rotation();
		return true;
	}

	return false;
}

