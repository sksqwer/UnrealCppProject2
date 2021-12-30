#include "CAim.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Component/CStateComponent.h"

UCAim::UCAim()
{
	CHelpers::GetAsset<UCurveFloat>(&Curve, "CurveFloat'/Game/Actions/C_Aim.C_Aim'");
}

void UCAim::BeginPlay(ACharacter* InCharacter)
{
	OwnerCharacter = InCharacter;
	SpringArm = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	Camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);

	TimelineFloat.BindUFunction(this, "Zooming");
	Timeline.AddInterpFloat(Curve, TimelineFloat);

	Timeline.SetPlayRate(200);
}

void UCAim::Tick(float DeltaTime)
{
	Timeline.TickTimeline(DeltaTime);
}

void UCAim::Zooming(float Value)
{
	//CLog::Log(Value, 0);
	Camera->FieldOfView = Value;
}

void UCAim::OnAim()
{
	CLog::Print("OnAim");
	CheckFalse(IsAvailable());
	CheckTrue(bInZoom);
	CLog::Print("OnAim2");

	bInZoom = true;

	SpringArm->TargetArmLength = 100.0f;
	SpringArm->SocketOffset = FVector(0, 30, 10.0f);
	SpringArm->bEnableCameraLag = false;
	//Camera->FieldOfView = 45;

	Timeline.PlayFromStart();
}

void UCAim::OffAim()
{
	CLog::Print("OffAim");
	CheckFalse(IsAvailable());
	CheckFalse(bInZoom);
	CLog::Print("OffAim2");

	bInZoom = false;

	SpringArm->TargetArmLength = 750.0f;
	SpringArm->SocketOffset = FVector(0, 0, 140.0);
	SpringArm->bEnableCameraLag = false;
	//Camera->FieldOfView = 90;

	Timeline.ReverseFromEnd();
}
