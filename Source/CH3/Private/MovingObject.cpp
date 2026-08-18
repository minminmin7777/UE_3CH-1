#include "MovingObject.h"

AMovingObject::AMovingObject()
{
 	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);//루트컴포넌트로 만들기

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	if (DefaultMesh)
	{
		StaticMeshComp->SetStaticMesh(DefaultMesh);
	}

	MoveSpeed = 90.0f;
	MoveDistance = 300.0f;

	Direction = 1.0f; //음수인지 양수인지로 x방향 정함

}
void AMovingObject::BeginPlay()
{
	Super::BeginPlay();	

	StartX = GetActorLocation().X;//이제 얘는 X 위치를 가짐 (x 값만). 내가 월드 배치하면 그 x값
}
void AMovingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!FMath::IsNearlyZero(MoveSpeed))
	{//AddActorLocalOffset 현재 위치에서 여기만큼 더 이동하라는 뜻!
		AddActorLocalOffset(FVector(Direction * MoveSpeed * DeltaTime, 0.0f, 0.0f));
		//FVector은 (x,y,z)임 , X축으로만 이동하는거임 위에

		float CurrentX = GetActorLocation().X;//액터 현재 위치

		if (FMath::Abs(CurrentX - StartX) >= MoveDistance)
		{//Abs는 절댓값.(현재값-시작값)으로 얼마나 이동했는지. 
		 //이동 거리가 MoveDistance와 같거나 크면 방향 바꿈 (안하면 한방향으로 계속 움직임)
			Direction *= -1.0f;
		}
		
	}
}

